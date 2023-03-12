/**
 * Implementation of BlockingQueue
 *
 * @version 0.1.0
 * @author Truman Kim (truman.t.kim@gmail.com)
 */
#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class BlockingQueue final {
  public:
    BlockingQueue() = default;

    ~BlockingQueue() {
        {
            std::unique_lock<std::mutex> lock(q_mutex_);
            destroyed_ = true;
        }
        q_condition_.notify_all();
    }

    void push(T &value) {
        {
            std::unique_lock<std::mutex> lock(q_mutex_);
            q_.push(std::move(value));
        }
        q_condition_.notify_one();
    }

    bool pop(T &popped) {
        std::unique_lock<std::mutex> lock(q_mutex_);
        q_condition_.wait(lock, [this] { return !q_.empty() || destroyed_; });
        if (destroyed_) {
            return false;
        }
        popped = q_.front();  // Assignment Operator
        q_.pop();             // Destructor
        return true;
    }

  private:
    std::queue<T> q_;
    std::mutex q_mutex_;
    std::condition_variable q_condition_;

    bool destroyed_;
};
