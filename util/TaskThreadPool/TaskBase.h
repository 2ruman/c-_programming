/**
 * Implementation of TaskBase interface
 *
 * @version 0.1.0
 * @author Truman Kim (truman.t.kim@gmail.com)
 */
#ifndef _TASK_BASE_H_
#define _TASK_BASE_H_

class TaskBase {
  public:
    virtual void prepare() {}
    virtual void work() = 0;
    virtual void report() {}
};

#endif  // _TASK_BASE_H_