/**
 * Implementation of TaskBase interface.
 *
 * @version 0.1.1
 * @author Truman Kim (truman.t.kim@gmail.com)
 */
#ifndef _TASK_BASE_H_
#define _TASK_BASE_H_

#include <atomic>

class TaskBase {
  public:
    static constexpr const long STEP_MS = 500;
    enum State {
        IDLE,
        RUNNING
    };
    TaskBase(int id) : id_(id) {
    }
    TaskBase() = default;
    ~TaskBase() = default;

    virtual void prepare() {}
    virtual void work() = 0;
    virtual void report() {}

    int getId() {
        return id_;
    }

    bool isPeriodic() {
        return (period_ > 0);
    }

    void setPeriod(long period) {
        if (period < 0) {
            period_ = 0;
        } else {
            period_ = period;
        }
    }

    bool checkAndResetTime() {
        if (curr_time_ >= period_) {
            curr_time_ = 0;
            return true;
        }
        return false;
    }

    long getTime() {
        return curr_time_;
    }

    void updateTime() {
        curr_time_ += STEP_MS;
    }

    bool isRunning() {
        return state_ == State::RUNNING;
    }

  protected:
    std::atomic<State> state_ = State::IDLE;
    int id_ = -1;
    long period_ = 0;
    long curr_time_ = 0;
};

#endif  // _TASK_BASE_H_