#include <iostream>

#include "ProcStatUtils.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cout << "Too few argument" << endl;
        return -1;
    }

    int pid = atoi(argv[1]);
    cout << "pid              : " << proc::stat::getProcStat(pid, proc::stat::NR_PID, -1) << endl;
    cout << "utime in jiffies : " << proc::stat::getProcStat(pid, proc::stat::NR_UTIME, -1) << endl;
    cout << "stime in jiffies : " << proc::stat::getProcStat(pid, proc::stat::NR_STIME, -1) << endl;
    cout << "CPU usage in sec : " << proc::stat::getProcCpuUsageInSec(pid) << endl;
    return 0;
}
