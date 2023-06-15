/**
 * This program is to test TaskScheduler implemented on
 * TaskScheduler.h in this project.
 *
 * @version 0.2.0
 * @author Truman Kim (truman.t.kim@gmail.com)
 */
#include <iostream>
#include <thread>

#include "Task.h"
#include "TaskInfo.h"
#include "TaskResult.h"
#include "TaskScheduler.h"

int main() {
    TaskInfo ti1(1);
    TaskInfo ti2(1);

    auto ext_reporter = [=](Task& self) {
        printf("%s%s\n", self.tag_.c_str(), "Reporting result in external reporter...");
        if (self.getResult().code() == TaskResult<decltype(self.getResult())>::NO_ERROR) {
            for (auto& s : self.getResult().get()) {
                printf("%s\n", s.c_str());
            }
        }
    };

    std::shared_ptr<Task> task_1 = std::make_shared<Task>(1, ti1);
    task_1->setWorker([](Task& self) {
        printf("%s%s\n", self.tag_.c_str(), "Now working...");
        std::vector<std::string> result;
        result.emplace_back("Hello, I'm Truman.");
        result.emplace_back("Nice to meet you!");
        printf("%s%s\n", self.tag_.c_str(), "Done!");
        self.getResult() = result;  // Parameterized Constructor
    });
    task_1->setPeriod(1000);

    std::shared_ptr<Task> task_2 = std::make_shared<Task>(2, ti2);
    task_2->setWorker([](Task& self) {
        printf("%s%s\n", self.tag_.c_str(), "Now working...");
        std::vector<std::string> result;
        result.emplace_back("What can I do for you?");
        printf("%s%s\n", self.tag_.c_str(), "Done!");
        self.getResult() = result;  // Parameterized Constructor
    });
    task_2->setReporter(ext_reporter);
    task_2->setPeriod(2000);

    std::unique_ptr<TaskScheduler> taskScheduler = std::make_unique<TaskScheduler>();
    taskScheduler->schedule(task_1);
    taskScheduler->schedule(task_2);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    taskScheduler->cancel(1);

    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "Test finished!" << std::endl;
    return 0;
}