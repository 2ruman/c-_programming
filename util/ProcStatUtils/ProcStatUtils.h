#pragma once

#include "FstreamUtils.h"

namespace proc {
namespace stat {

#ifndef CLT_TCK
#define CLK_TCK 100  // This value depends on your system configuration
                     // (You can check it by "getconf CLK_TCK" command)
#endif

const int NR_PID = 1;
const int NR_PPID = 4;
const int NR_UTIME = 14;
const int NR_STIME = 15;
const int NR_START_TIME = 22;

long getProcStat(int pid, int nr, long defaultVal) {
    std::string filename;
    std::string line;

    filename = "/proc/" + std::to_string(pid) + "/stat";

    std::ifstream stat_file(filename);
    if (!stat_file.is_open()) {
        return defaultVal;
    }
    return getNthLong(stat_file, nr, defaultVal);
}

long getProcCpuUsageInJiffies(int pid) {
    long utime = getProcStat(pid, NR_UTIME, -1);
    long stime = getProcStat(pid, NR_STIME, -1);
    if (utime < 0 || stime < 0) {
        return -1;
    }
    return utime + stime;
}

long getProcCpuUsageInSec(int pid, unsigned int clock_tick = CLK_TCK) {
    long jiffies = getProcCpuUsageInJiffies(pid);
    if (jiffies < 0) {
        return 0;
    }
    return jiffies / clock_tick;
}

}  // namespace stat
}  // namespace proc