/**
 * This program is to test TaskScheduler implemented on
 * TaskScheduler.h in this project.
 *
 * @version 0.1.0
 * @author Truman Kim (truman.t.kim@gmail.com)
 */
#include <iostream>
#include <thread>

#include "TaskBase.h"
#include "TaskInfo.h"
#include "TaskResult.h"
#include "TaskScheduler.h"

class Task : public TaskBase {
  public:
    ~Task() {
    }

    Task(int id) : TaskBase(id) {
        tag_ = " Task(" + std::to_string(id_) + ") :: ";
    }

    Task(int id, TaskInfo& ti)
        : TaskBase(id), ti_(ti) {
        tag_ = "Task(" + std::to_string(id_) + ") :: ";
    }

    Task(const Task& t) : ti_(t.ti_), result_(t.result_) {
    }

    Task(Task&& t) : ti_(t.ti_), result_(t.result_) {
    }

    void setWork(std::function<void(Task&)>&& func) {
        if (func) {
            work_ = func;
        }
    }

    void prepare() {
        printf("%s%s\n", tag_.c_str(), "Preparing to work...");
        state_ = State::RUNNING;
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
                printf("%s\n", s.c_str());
            }
        }
        state_ = State::IDLE;
    }

    TaskInfo& getInfo() {
        return ti_;
    }

    TaskResult<std::vector<std::string>>& getResult() {
        return result_;
    }
    std::string tag_;

  protected:
    TaskInfo ti_;
    TaskResult<std::vector<std::string>> result_;
    std::function<void(Task&)> work_;
};

int main() {
    TaskInfo ti1(1);
    TaskInfo ti2(1);

    std::shared_ptr<Task> task_1 = std::make_shared<Task>(1, ti1);
    task_1->setWork([](Task& self) {
        printf("%s%s\n", self.tag_.c_str(), "Now working...");
        std::vector<std::string> result;
        result.emplace_back("Hello, I'm Truman.");
        result.emplace_back("Nice to meet you!");
        printf("%s%s\n", self.tag_.c_str(), "Done!");
        self.getResult() = result;  // Parameterized Constructor
    });
    task_1->setPeriod(1000);

    std::shared_ptr<Task> task_2 = std::make_shared<Task>(2, ti2);
    task_2->setWork([](Task& self) {
        printf("%s%s\n", self.tag_.c_str(), "Now working...");
        std::vector<std::string> result;
        result.emplace_back("What can I do for you?");
        printf("%s%s\n", self.tag_.c_str(), "Done!");
        self.getResult() = result;  // Parameterized Constructor
    });
    task_2->setPeriod(2000);

    std::unique_ptr<TaskScheduler> taskScheduler = std::make_unique<TaskScheduler>();
    taskScheduler->schedule(task_1);
    taskScheduler->schedule(task_2);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    taskScheduler->cancel(1);

    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "Test finished!" << std::endl;
    return 0;
}