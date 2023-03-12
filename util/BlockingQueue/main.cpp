/**
 * This program is to test BlockingQueue implemented through
 * BlockingQueue.h in the project.
 * 
 * @version 0.1.0
 * @author Truman Kim (truman.t.kim@gmail.com)
 */
#include <iostream>
#include <thread>

#include "Task.h"

int main() {
    TaskHandler taskHandler;
    TaskInjector taskInjector(taskHandler);

    std::this_thread::sleep_for(std::chrono::seconds(WAITING_TASKS_TIME_SEC));
    std::cout << "Test finished!" << std::endl;
    return 0;
}