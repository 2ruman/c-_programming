/**
 * Implementation of TaskInfo that contains
 * information of corresponding task to be done.
 *
 * @version 0.1.0
 * @author Truman Kim (truman.t.kim@gmail.com)
 */
#ifndef _TASK_INFO_H_
#define _TASK_INFO_H_

class TaskInfo {
  public:
    ~TaskInfo() {
    }
    TaskInfo() : type_(-1) {
    }
    TaskInfo(int task_type) : type_(task_type) {
    }
    TaskInfo(const TaskInfo& ti)
        : type_(ti.type_), ch_val_(ti.ch_val_) {
    }
    TaskInfo(TaskInfo&& ti)
        : type_(ti.type_), ch_val_(ti.ch_val_) {
    }
    TaskInfo& operator=(const TaskInfo& ti) {
        this->type_ = ti.type_;
        this->ch_val_ = ti.ch_val_;
        return *this;
    }

    int getType() {
        return type_;
    }
    void setCh(char&& ch) {
        ch_val_ = ch;
    }
    char& getCh() {
        return ch_val_;
    }

  private:
    int type_;     // Member for example
    char ch_val_;  // Member for example
};

#endif  // _TASK_INFO_H_