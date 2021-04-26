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
float Process::CpuUtilization() const { return this->cpu_usage; }

// DONE: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(this->pid); }

// DONE: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(this->pid); }

// DONE: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(this->pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  return this->CpuUtilization() < a.CpuUtilization();
}

bool Process::operator>(Process const& a) const { 
  return this->CpuUtilization() > a.CpuUtilization();
}