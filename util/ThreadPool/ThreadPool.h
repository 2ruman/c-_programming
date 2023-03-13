#include <cstddef>  // For size_t

class ThreadPool {
  public:
    ThreadPool(size_t);

  private:
    bool stop_;
};