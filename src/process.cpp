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
float Process::CpuUtilization() const { return this->cpu_usage_; }

void Process::CpuUtilization(long active_ticks, long system_ticks) {
  long duration_active{active_ticks - cached_active_ticks_};
  long duration{system_ticks - cached_system_ticks_};
  cpu_usage_ = static_cast<float>(duration_active) / duration;
  cached_active_ticks_ = active_ticks;
  cached_system_ticks_ = system_ticks;
}

// DONE: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(this->pid); }

// DONE: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(this->pid); }

// DONE: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(this->pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(this->pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  return this->CpuUtilization() < a.CpuUtilization();
}

bool Process::operator>(Process const& a) const { 
  return this->CpuUtilization() > a.CpuUtilization();
}