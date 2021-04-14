#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// DONE: Return this process's ID
int Process::Pid() { return this->pid; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() {
  string line, token;
  std::ifstream filestream(LinuxParser::kProcDirectory + std::to_string(this->pid) + LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    if (std::getline (filestream, line)) {
      std::stringstream linestream(line);
      procCPUvalues.clear();
      while (linestream >> token) {
        this->procCPUvalues.push_back(atol(token.c_str()));
      }
    }
  }
  long utime = procCPUvalues[13];      // #14 utime - CPU time spent in user code, measured in clock ticks
  long stime = procCPUvalues[14];      // #15 stime - CPU time spent in kernel code, measured in clock ticks
  long cutime = procCPUvalues[15];     // #16 cutime - Waited-for children's CPU time spent in user code (in clock ticks)
  long cstime = procCPUvalues[16];     // #17 cstime - Waited-for children's CPU time spent in kernel code (in clock ticks)
  long starttime = procCPUvalues[21];  // #22 starttime - Time when the process started, measured in clock ticks

  long Hertz = sysconf(_SC_CLK_TCK);

  long total_time = utime + stime + cutime + cstime;

  float seconds = LinuxParser::UpTime() - (starttime / Hertz);

  float cpu_usage = 100 * ((total_time / Hertz) / seconds);

  return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(this->pid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(this->pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }