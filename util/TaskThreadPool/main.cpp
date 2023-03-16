

/**
 * This program is to test TaskThreadPool implemented on
 * TaskThreadPool.h in this project.
 *
 * @version 0.1.0
 * @author Truman Kim (truman.t.kim@gmail.com)
 */

#include "TaskExamples.h"
#include "TaskThreadPool.h"

int main() {
    TaskInfo ti1(1);
    ti1.setCh('a');
    TaskInfo ti2(1);
    ti2.setCh('k');
    TaskInfo ti3(2);
    ti3.setCh('0');
    TaskInfo ti4(1);
    ti4.setCh('u');

    TaskThreadPool pool(3);
    pool.schedule(std::make_shared<TaskA>(ti1));
    pool.schedule(std::make_shared<TaskB>(ti1));
    pool.schedule(std::make_shared<TaskC>(ti3));
    pool.schedule(std::make_shared<TaskD>(ti1));
    pool.schedule(std::make_shared<TaskA>(ti2));
    pool.schedule(std::make_shared<TaskB>(ti4));

    return 0;
}