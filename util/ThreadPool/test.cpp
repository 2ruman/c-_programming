#include <chrono>
#include <cmath>

void compute_square_root(double x) {
    std::cout << "Thread " << std::this_thread::get_id() << " computing square root of " << x << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    double result = std::sqrt(x);
    std::cout << "Thread " << std::this_thread::get_id() << " result: " << result << "\n";
}

int main() {
    ThreadPool pool(2);

    std::vector<std::future<void>> results;

    for (double x : {0.1, 1.0, 10.0, 100.0, 1000.0}) {
        results.emplace_back(
            pool.enqueue(compute_square_root, x));
    }

    for (auto& result : results) {
        result.get();
    }

    return 0;
}
