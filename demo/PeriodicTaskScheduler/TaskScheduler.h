/**
 * Implementation of TaskScheduler
 *
 * @version 0.1.0
 * @author Truman Kim (truman.t.kim@gmail.com)
 */
#include <condition_variable>
#include <deque>
#include <mutex>
#include <thread>

#include "TaskBase.h"
#include "TaskThreadPool.h"

#define TASK_POOL_SIZ 2

class TaskScheduler final {
  public:
    TaskScheduler() {
        pool_ = std::make_unique<TaskThreadPool>(TASK_POOL_SIZ);

        scheduler_ = std::thread(
            [this] {
                {
                    std::unique_lock<std::mutex> lock(tq_mutex_);
                    tq_condition_.wait(lock, [this] { return !tasks_.empty() || destroyed_; });

                    std::shared_ptr<TaskBase> task;
                    std::deque<std::shared_ptr<TaskBase>> tmp_tasks;

                    while (!tasks_.empty()) {
                        task = tasks_.front();

                        if (task->isPeriodic()) {
                            task->updateTime();
                            if (task->checkAndResetTime()) {
                                if (!task->isRunning()) {
                                    pool_->schedule(task);
                                } else {
                                    std::cout << "Task is still running!!!!" << std::endl;
                                }
                            }
                            tmp_tasks.push_back(task);
                        } else {
                            pool_->schedule(task);
                        }
                        tasks_.pop_front();
                    }
                    if (destroyed_) {
                        return;
                    }
                    tasks_ = tmp_tasks;  // Reschedule
                }
                if (TaskBase::STEP_MS > 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(TaskBase::STEP_MS));
                }
            });
    }

    ~TaskScheduler() {
        {
            std::unique_lock<std::mutex> lock(tq_mutex_);
            destroyed_ = true;
        }
        tq_condition_.notify_all();
        scheduler_.join();
    }

    void schedule(const std::shared_ptr<TaskBase>& task) {
        {
            std::unique_lock<std::mutex> lock(tq_mutex_);
            tasks_.push_back(task);
        }
        tq_condition_.notify_one();
    }

    bool cancel(int task_id) {
        std::lock_guard<std::mutex> lock(tq_mutex_);
        for (auto it = tasks_.cbegin(); it != tasks_.cend(); it++) {
            if (it->get()->getId() == task_id) {
                it->get()->setPeriod(0);
                return true;
            }
        }
        return false;
    }

  private:
    std::unique_ptr<TaskThreadPool> pool_;         // Task Proccessing Pool
    std::thread scheduler_;                        // Main Scheduler
    std::mutex tq_mutex_;                          // Lock for Task Queue
    std::deque<std::shared_ptr<TaskBase>> tasks_;  // Task Queue
    std::condition_variable tq_condition_;         // Condition Variable for Task Queue
    bool destroyed_;
};
