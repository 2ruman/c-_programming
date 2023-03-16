/**
 * This program is to test TaskScheduler implemented on
 * TaskScheduler.h in this project.
 *
 * @version 0.1.0
 * @author Truman Kim (truman.t.kim@gmail.com)
 */
#include <iostream>
#include <thread>

// #include "Task.h"
#include "TaskInfo.h"
#include "TaskResult.h"
#include "TaskScheduler.h"

#define DEBUG_TASK_LIFECYCLE true

class Task : public TaskBase {
  public:
    ~Task() {
        // if (DEBUG) std::cout << TAG << "Destructor!" << std::endl;
    }
    Task(int id) : TaskBase(id) {
        tag_ = " Task(" + std::to_string(id_) + ") :: ";
        // if (DEBUG) std::cout << TAG << "Default Constructor!" << std::endl;
    }
    Task(int id, TaskInfo& ti)
        : TaskBase(id), ti_(ti) {
        tag_ = "Task(" + std::to_string(id_) + ") :: ";
        // if (DEBUG) std::cout << TAG << "Parameterized Constructor!" << std::endl;
    }
    Task(const Task& t) : ti_(t.ti_), result_(t.result_) {
        // if (DEBUG) std::cout << TAG << "Copy Constructor!" << std::endl;
    }
    Task(Task&& t) : ti_(t.ti_), result_(t.result_) {
        // if (DEBUG) std::cout << TAG << "Move Consturctor!" << std::endl;
    }

    void setWork(std::function<void(Task&)>&& func) {
        if (func) {
            work_ = func;
        }
    }

    void prepare() {
        printf("%s%s\n", tag_.c_str(), "Preparing to work...");
    }

    void work() override {
        if (work_) {
            work_(*this);
        }
    }

    void report() {
        printf("%s%s\n", tag_.c_str(), "Reporting result...");
        if (result_.code() == TaskResult<decltype(result_)>::NO_ERROR) {
            for (auto& s : result_.get()) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                printf("%s\n", s.c_str());
            }
        }
    }

    TaskInfo& getInfo() {
        return ti_;
    }

    TaskResult<std::vector<std::string>>& getResult() {
        return result_;
    }
    std::string tag_;

  protected:
    static constexpr const bool DEBUG = DEBUG_TASK_LIFECYCLE;
    TaskInfo ti_;
    TaskResult<std::vector<std::string>> result_;
    std::function<void(Task&)> work_;
};

int main() {
    TaskInfo ti1(1);
    ti1.setCh('a');

    std::shared_ptr<Task> task_1 = std::make_shared<Task>(1, ti1);
    task_1->setWork([](Task& self) {
        printf("%s%s\n", self.tag_.c_str(), "Now working...");
        std::vector<std::string> result;
        char& ch = self.getInfo().getCh();

        for (int i = 0; i < 10; i++) {
            result.emplace_back(1, std::toupper(ch++));
        }
        printf("%s%s\n", self.tag_.c_str(), "Done!");
        self.getResult() = result;  // Parameterized Constructor
    });
    // task_1->setPeriod(1000);

    std::cout << "Start schedule!" << std::endl;
    std::shared_ptr<TaskScheduler> taskScheduler = std::make_shared<TaskScheduler>();
    taskScheduler->schedule(task_1);

    std::this_thread::sleep_for(std::chrono::seconds(20));
    std::cout << "Test finished!" << std::endl;
    return 0;
}