/**
 * Implementation of Task that implements TaskBase interface.
 * It has assignable worker and reporter.
 *
 * @version 0.1.0
 * @author Truman Kim (truman.t.kim@gmail.com)
 */

#ifndef _TASK_H_
#define _TASK_H_

#include <functional>
#include <string>
#include <vector>

#include "TaskBase.h"
#include "TaskInfo.h"
#include "TaskResult.h"

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

    void setWorker(std::function<void(Task&)>&& worker) {
        if (worker) {
            worker_ = worker;
        }
    }

    void setReporter(std::function<void(Task&)>&& reporter) {
        if (reporter) {
            reporter_ = reporter;
        }
    }

    void prepare() override {
        printf("%s%s\n", tag_.c_str(), "Preparing to work...");
        state_ = State::RUNNING;
    }

    void work() override {
        if (worker_) {
            worker_(*this);
        }
    }

    void report() override {
        if (reporter_) {
            reporter_(*this);
        } else {
            printf("%s%s\n", tag_.c_str(), "Reporting result in internal reporter...");
            if (result_.code() == TaskResult<decltype(result_)>::NO_ERROR) {
                for (auto& s : result_.get()) {
                    printf("%s\n", s.c_str());
                }
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
    std::function<void(Task&)> worker_;
    std::function<void(Task&)> reporter_;
};

#endif  // _TASK_H_