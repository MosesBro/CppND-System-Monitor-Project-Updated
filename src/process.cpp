#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::vector;

// Return this process's ID
int Process::Pid() const { return this->pid; }

// Return this process's CPU utilization
float Process::CpuUtilization() const { return this->cpu_usage_; }

void Process::CpuUtilization(long active_ticks, long system_ticks) {
  long duration_active{active_ticks - cached_active_ticks_};
  long duration{system_ticks - cached_system_ticks_};
  cpu_usage_ = static_cast<float>(duration_active) / duration;
  cached_active_ticks_ = active_ticks;
  cached_system_ticks_ = system_ticks;
}

// Return the command that generated this process
string Process::Command() const { return LinuxParser::Command(this->pid); }

// Return this process's memory utilization
string Process::Ram() const { return LinuxParser::Ram(this->pid); }

// Return the user (name) that generated this process
string Process::User() const { return LinuxParser::User(this->pid); }

// Return the age of this process (in seconds)
long int Process::UpTime() const { return LinuxParser::UpTime(this->pid); }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { 
  return this->CpuUtilization() < a.CpuUtilization();
}

// Overload the "greater than" comparison operator for Process objects
bool Process::operator>(Process const& a) const { 
  return this->CpuUtilization() > a.CpuUtilization();
}