
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class BlockingQueue final {
  public:
    BlockingQueue() = default;

    ~BlockingQueue();

    void push(T value) {
      {
          std::unique_lock<std::mutex> lock(q_mutex_);
          q_.push(std::move(value));
      }
      q_condition_.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(q_mutex_);
       q_condition_.wait(lock, [this] { return !q_.empty(); });
       T value = std::move(q_.front());
       q_.pop();
        return value;
    }

  private:
    BlockingQueue(const BlockingQueue<T>& bq);

    std::queue<T> q_;
    std::mutex q_mutex_;
    std::condition_variable q_condition_;
};
