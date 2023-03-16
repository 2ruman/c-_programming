/**
 * Example of using BlockingQueue by Producer/Consumer
 *
 * @version 0.1.0
 * @author Truman Kim (truman.t.kim@gmail.com)
 */
#include <iostream>
#include <thread>

#include "BlockingQueue.h"

// Configurations
#define DEBUG_TASK_LIFECYCLE false
#define PRODUCING_TASKS_CNT 10
#define WAITING_TASKS_TIME_SEC 5
#define PROCESSING_TASK_TIME_SEC 1

class Task {
  public:
    Task() = default;
    Task(int id) : id_(id) {
        if (DEBUG)
            std::cout << "Task Parameterized Constructor - " << id_ << std::endl;
    }
    Task(const Task &task) : id_(task.id_) {
        if (DEBUG)
            std::cout << "Task Copy Constructor - " << id_ << std::endl;
    }
    Task(Task &&task) : id_(task.id_) {
        if (DEBUG)
            std::cout << "Task Move Constructor - " << id_ << std::endl;
    }
    Task &operator=(const Task &task) {
        this->id_ = task.id_;
        if (DEBUG)
            std::cout << "Task Assignment Operator - " << id_ << std::endl;
        return *this;
    }
    ~Task() {
        if (DEBUG)
            std::cout << "Task Destructor - " << id_ << std::endl;
    }
    void execute() {
        std::cout << "Task(" << id_ << ") is now being processed..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(PROCESSING_TASK_TIME_SEC));
        std::cout << "Task(" << id_ << ") has been done!" << std::endl;
    }

  private:
    static const bool DEBUG = DEBUG_TASK_LIFECYCLE;
    int id_;
};

class TaskHandler {
  public:
    TaskHandler() : stop_(false) {
        bq_ = std::make_unique<BlockingQueue<Task>>();
        looper_ = std::thread([this] {
            while (!stop_) {
                if (bq_->pop(curr_task_)) {
                    curr_task_.execute();
                }
            }
        });
    }

    void request(Task &task) { bq_->push(task); }

    ~TaskHandler() {
        stop_ = true;
        bq_.reset();
        looper_.join();
    }

  private:
    std::unique_ptr<BlockingQueue<Task>> bq_;
    std::thread looper_;
    Task curr_task_;
    bool stop_;
};

class TaskInjector {
  public:
    TaskInjector(TaskHandler &task_handler) {
        std::thread injector([&task_handler] {
            for (int i = 0; i < PRODUCING_TASKS_CNT; i++) {
                Task task(i);
                task_handler.request(task);
            }
        });
        injector.join();
    }
};