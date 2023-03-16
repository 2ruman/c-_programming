/**
 * Implementation of TaskResult that contains
 * result, result code and error information that
 * are made druing corresponding task.
 *
 * @version 0.1.0
 * @author Truman Kim (truman.t.kim@gmail.com)
 */
#ifndef _TASK_RESULT_H_
#define _TASK_RESULT_H_

template <typename T>
class TaskResult {
  public:
    static constexpr const int NO_ERROR = 0;
    static constexpr const int INTERNAL_ERROR = -400;

    TaskResult() : code_(NO_ERROR) {
    }
    TaskResult(const T& result)
        : code_(NO_ERROR), result_(result) {
    }
    TaskResult(const TaskResult<T>& result)
        : code_(NO_ERROR), result_(result.result_), err_msg_(result.err_msg_) {
    }

    int code() {
        return code_;
    }

    const T& get() {
        return result_;
    }

    void setErr(int code, const std::string& err_msg) {
        code_ = code;
        err_msg_ = err_msg;
    }

    const std::string& getErrMsg() {
        return err_msg_;
    }

  private:
    int code_;
    T result_;
    std::string err_msg_;
};

#endif  // _TASK_RESULT_H_