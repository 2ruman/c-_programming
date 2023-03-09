
#include "BlockingQueue.h"

// template <typename T>
// void BlockingQueue<T>::push(T value) {
//     {
//         std::unique_lock<std::mutex> lock(q_mutex_);
//         q_.push(std::move(value));
//     }
//     q_condition_.notify_one();
// }

// template <typename T>
// T BlockingQueue<T>::pop() {
//     std::unique_lock<std::mutex> lock(q_mutex_);
//     q_condition_.wait(lock, [this] { return !q_.empty(); });
//     T value = std::move(q_.front());
//     q_.pop();
//     return value;
// }

template <typename T>
BlockingQueue<T>::~BlockingQueue<T>() {

}