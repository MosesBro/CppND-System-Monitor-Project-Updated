#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid() const;
  std::string User() const;
  std::string Command() const;
  float CpuUtilization() const;
  void CpuUtilization(long, long);
  std::string Ram() const;
  long int UpTime() const;
  bool operator<(Process const& a) const;
  bool operator>(Process const& a) const;
  Process(int pid) : pid(pid), cached_active_ticks_(0) {};

 private:
  int pid{0};
  float cpu_usage_{0};
  long cached_active_ticks_{0}, cached_system_ticks_{0};
};

#endif