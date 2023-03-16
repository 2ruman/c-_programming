
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "TaskBase.h"
#include "TaskInfo.h"
#include "TaskResult.h"

#define DEBUG_TASK_LIFECYCLE false

class TaskA : public TaskBase {
  public:
    ~TaskA() {
        if (DEBUG) std::cout << TAG << "Destructor!" << std::endl;
    }
    TaskA() {
        if (DEBUG) std::cout << TAG << "Default Constructor!" << std::endl;
    }
    TaskA(TaskInfo& ti) : ti_(ti) {
        if (DEBUG) std::cout << TAG << "Parameterized Constructor!" << std::endl;
    }
    TaskA(const TaskA& t) : ti_(t.ti_), result_(t.result_) {
        if (DEBUG) std::cout << TAG << "Copy Constructor!" << std::endl;
    }
    TaskA(TaskA&& t) : ti_(t.ti_), result_(t.result_) {
        if (DEBUG) std::cout << TAG << "Move Consturctor!" << std::endl;
    }

    void prepare() {
        printf("%s%s\n", TAG, "Preparing to work...");
    }

    void work() override {
        printf("%s%s\n", TAG, "Now working...");
        std::vector<std::string> result;
        char& ch = ti_.getCh();
        for (int i = 0; i < 10; i++) {
            result.emplace_back(1, std::toupper(ch++));
        }
        printf("%s%s\n", TAG, "Done!");
        result_ = result;  // Parameterized Constructor
    }

    void report() {
        if (result_.code() == TaskResult<decltype(result_)>::NO_ERROR) {
            for (auto& s : result_.get()) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                printf("%s\n", s.c_str());
            }
        }
    }

  protected:
    static constexpr const char* TAG = "TaskA :: ";
    static constexpr const bool DEBUG = DEBUG_TASK_LIFECYCLE;
    TaskInfo ti_;
    TaskResult<std::vector<std::string>> result_;
};

// Copy-and-pasted from TaskA class
class TaskB : public TaskBase {
  public:
    ~TaskB() {
        if (DEBUG) std::cout << TAG << "Destructor!" << std::endl;
    }
    TaskB() {
        if (DEBUG) std::cout << TAG << "Default Constructor!" << std::endl;
    }
    TaskB(TaskInfo& ti) : ti_(ti) {
        if (DEBUG) std::cout << TAG << "Parameterized Constructor!" << std::endl;
    }
    TaskB(const TaskB& t) : ti_(t.ti_), result_(t.result_) {
        if (DEBUG) std::cout << TAG << "Copy Constructor!" << std::endl;
    }
    TaskB(TaskB&& t) : ti_(t.ti_), result_(t.result_) {
        if (DEBUG) std::cout << TAG << "Move Consturctor!" << std::endl;
    }

    void prepare() {
        printf("%s%s\n", TAG, "Preparing to work...");
    }

    void work() override {
        printf("%s%s\n", TAG, "Now working...");
        std::vector<std::string> result;
        char& ch = ti_.getCh();
        for (int i = 0; i < 10; i++) {
            std::string s(1, ' ');
            s += ch++;
            result.push_back(s);
        }
        printf("%s%s\n", TAG, "Done!");
        result_ = result;  // Parameterized Constructor
    }

    void report() {
        if (result_.code() == TaskResult<decltype(result_)>::NO_ERROR) {
            for (auto& s : result_.get()) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                printf("%s\n", s.c_str());
            }
        }
    }

  protected:
    static constexpr const char* TAG = "TaskB :: ";
    static constexpr const bool DEBUG = DEBUG_TASK_LIFECYCLE;
    TaskInfo ti_;
    TaskResult<std::vector<std::string>> result_;
};

// Copy-and-pasted from TaskA class
class TaskC : public TaskBase {
  public:
    ~TaskC() {
        if (DEBUG) std::cout << TAG << "Destructor!" << std::endl;
    }
    TaskC() {
        if (DEBUG) std::cout << TAG << "Default Constructor!" << std::endl;
    }
    TaskC(TaskInfo& ti) : ti_(ti) {
        if (DEBUG) std::cout << TAG << "Parameterized Constructor!" << std::endl;
    }
    TaskC(const TaskC& t) : ti_(t.ti_), result_(t.result_) {
        if (DEBUG) std::cout << TAG << "Copy Constructor!" << std::endl;
    }
    TaskC(TaskC&& t) : ti_(t.ti_), result_(t.result_) {
        if (DEBUG) std::cout << TAG << "Move Consturctor!" << std::endl;
    }

    void prepare() {
        printf("%s%s\n", TAG, "Preparing to work...");
    }

    void work() override {
        printf("%s%s\n", TAG, "Now working...");
        std::vector<std::string> result;
        char& ch = ti_.getCh();
        for (int i = 0; i < 10; i++) {
            std::string s(2, ' ');
            s += ch++;
            result.push_back(s);
        }
        printf("%s%s\n", TAG, "Done!");
        result_ = result;  // Parameterized Constructor
    }

    void report() {
        if (result_.code() == TaskResult<decltype(result_)>::NO_ERROR) {
            for (auto& s : result_.get()) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                printf("%s\n", s.c_str());
            }
        }
    }

  protected:
    static constexpr const char* TAG = "TaskC :: ";
    static constexpr const bool DEBUG = DEBUG_TASK_LIFECYCLE;
    TaskInfo ti_;
    TaskResult<std::vector<std::string>> result_;
};

// Copy-and-pasted from TaskA class
class TaskD : public TaskBase {
  public:
    ~TaskD() {
        if (DEBUG) std::cout << TAG << "Destructor!" << std::endl;
    }
    TaskD() {
        if (DEBUG) std::cout << TAG << "Default Constructor!" << std::endl;
    }
    TaskD(TaskInfo& ti) : ti_(ti) {
        if (DEBUG) std::cout << TAG << "Parameterized Constructor!" << std::endl;
    }
    TaskD(const TaskD& t) : ti_(t.ti_), result_(t.result_) {
        if (DEBUG) std::cout << TAG << "Copy Constructor!" << std::endl;
    }
    TaskD(TaskD&& t) : ti_(t.ti_), result_(t.result_) {
        if (DEBUG) std::cout << TAG << "Move Consturctor!" << std::endl;
    }

    void prepare() {
        printf("%s%s\n", TAG, "Preparing to work...");
    }

    void work() override {
        printf("%s%s\n", TAG, "Now working...");
        // Error
        printf("%s%s\n", TAG, "Done!");
        result_.setErr(TaskResult<decltype(result_)>::INTERNAL_ERROR,
                       "Intended Error while working on TaskD :-p");
    }

    void report() {
        if (result_.code() != TaskResult<decltype(result_)>::NO_ERROR) {
            printf("Error:\n\t%s\n", result_.getErrMsg().c_str());
        }
    }

  protected:
    static constexpr const char* TAG = "TaskD :: ";
    static constexpr const bool DEBUG = DEBUG_TASK_LIFECYCLE;
    TaskInfo ti_;
    TaskResult<std::vector<std::string>> result_;
};