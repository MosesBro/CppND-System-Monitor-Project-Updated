#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::string;
using std::vector;

// Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// Return a container composed of the system's processes
vector<Process>& System::Processes() { 

    // Get a list of all the process IDs
    vector<int> pids = LinuxParser::Pids();
    processes_.clear();

    // Create Process objects and place in vector
    for (auto &&pid : pids)
    {
        processes_.emplace_back(Process(pid));
    }

    for (auto& process : processes_) {
    process.CpuUtilization(LinuxParser::ActiveJiffies(process.Pid()),
                           LinuxParser::Jiffies());
    }

    std::sort (processes_.begin(), processes_.end(), std::greater<Process>());

    return processes_; 
}

// Return the system's kernel identifier (string)
std::string System::Kernel() const { return LinuxParser::Kernel(); }

// Return the system's memory utilization
float System::MemoryUtilization() const { return LinuxParser::MemoryUtilization(); }

// Return the operating system name
std::string System::OperatingSystem() const { return LinuxParser::OperatingSystem(); }

// Return the number of processes actively running on the system
int System::RunningProcesses() const { return LinuxParser::RunningProcesses(); }

// Return the total number of processes on the system
int System::TotalProcesses() const { return LinuxParser::TotalProcesses(); }

// Return the number of seconds since the system started running
long int System::UpTime() const { return LinuxParser::UpTime(); }