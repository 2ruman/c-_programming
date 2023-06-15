/**
 * Implementation of TaskBase interface.
 *
 * @version 0.2.0
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
        RUNNING,
        CANCELED
    };
    TaskBase(int id) : TaskBase(id, 0) {
    }
    TaskBase(int id, int type) : id_(id), type_(type) {
    }
    TaskBase() = default;
    ~TaskBase() = default;

    virtual void prepare() {}
    virtual void work() = 0;
    virtual void report() {}

    int getId() {
        return id_;
    }

    int getType() {
        return type_;
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

    bool isRunnable() {
        return state_ == State::IDLE;
    }

    void cancel() {
        state_ = State::CANCELED;
        setPeriod(0);
    }

  protected:
    std::atomic<State> state_ = State::IDLE;
    int id_ = -1;
    int type_ = 0;
    long period_ = 0;
    long curr_time_ = 0;
};

#endif  // _TASK_BASE_H_