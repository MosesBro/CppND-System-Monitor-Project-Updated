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
  int Pid();                               // DONE: See src/process.cpp
  std::string User();                      // DONE: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization() const;            // TODO: See src/process.cpp
  void CpuUtilization(long, long);
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // DONE: See src/process.cpp
  bool operator>(Process const& a) const;  // DONE: See src/process.cpp
  Process(int pid) : pid(pid), cached_active_ticks_(0) {};

  // TODO: Declare any necessary private members
 private:
  int pid{0};
  float cpu_usage_{0};
  long cached_active_ticks_{0}, cached_system_ticks_{0};
};

#endif