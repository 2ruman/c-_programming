/**
 * Implementation of TaskThreadPool
 *
 * @version 0.1.0
 * @author Truman Kim (truman.t.kim@gmail.com)
 */
#ifndef _TASK_THREAD_POOL_H_
#define _TASK_THREAD_POOL_H_

#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "TaskBase.h"

class TaskThreadPool final {
  public:
    TaskThreadPool(size_t num_threads) : stopped_(false) {
        for (size_t i = 0; i < num_threads; ++i)
            threads_.emplace_back(
                [this] {
                    for (;;) {
                        std::shared_ptr<TaskBase> task;
                        {
                            std::unique_lock<std::mutex> lock(tq_mutex_);
                            tp_condition_.wait(lock, [this] { return !tasks_.empty() || stopped_; });
                            if (tasks_.empty() && stopped_) {
                                return;
                            }
                            task = tasks_.front();
                            tasks_.pop();
                        }
                        task->prepare();
                        task->work();
                        task->report();
                    }
                });
    }

    void schedule(const std::shared_ptr<TaskBase>& task) {
        std::lock_guard<std::mutex> lock(tq_mutex_);
        tasks_.push(task);
    }

    ~TaskThreadPool() {
        {
            std::unique_lock<std::mutex> lock(tq_mutex_);
            stopped_ = true;
        }
        tp_condition_.notify_all();
        for (std::thread& thread : threads_)
            thread.join();
    }

  private:
    std::queue<std::shared_ptr<TaskBase>> tasks_;
    std::condition_variable tp_condition_;
    std::vector<std::thread> threads_;
    std::mutex tq_mutex_;
    bool stopped_;
};

#endif  // _TASK_THREAD_POOL_H_