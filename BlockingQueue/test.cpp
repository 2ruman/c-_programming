
#include <iostream>
#include <thread>

#include "BlockingQueue.h"

class Task {
  private:
    int id_;

  public:
    Task(int id) : id_(id) {
        std::cout << "Task 일반생성자" << std::endl;
    }
    Task(const Task& task) {
        std::cout << "Task 복사생성자" << std::endl;
    }
    Task(Task&& task) {
        std::cout << "Task 이동생성자" << std::endl;
    }
    void execute() {
        std::cout << "Task(" << id_ << ") has been done!" << std::endl;
    }
};

class TaskHandler {
  private:
    BlockingQueue<Task> *bq_;
    bool stop;
    std::thread looper;

  public:
    TaskHandler() : stop(false) {
        bq_ = new BlockingQueue<Task>;
        looper = std::thread([this] {
            while (stop) {
                Task task = bq_->pop();
                task.execute();

            }
        });
    }

    void request(Task task) {
        bq_->push(task);
    }

    void terminate() {
        stop = true;
        looper.join();
    }
};

int main() {
    std::cout << "Program started!" << std::endl;

    TaskHandler taskHandler;
    taskHandler.terminate();

    std::cout << "Program ended!" << std::endl;
    return 0;
}