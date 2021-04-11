#include <vector>
#include <string>
#include "processor.h"
#include "linux_parser.h"

// Constructor
Processor::Processor() {
    this->prevCPUvalues = stringValuesToInt( LinuxParser::CpuUtilization() );
}

std::vector<int> stringValuesToInt(std::vector<std::string> CPUvalues) {
    std::vector<int> result{};
    for (auto &&value : CPUvalues)
    {
        result.push_back( atoi(value.c_str()));
    }
    return result;
}

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
    // Grab new CPU values
    std::vector<int> currCPUvalues = stringValuesToInt( LinuxParser::CpuUtilization() );
    
    // PrevIdle = previdle + previowait
    // Idle = idle + iowait
    int PrevIdle =  this->prevCPUvalues[LinuxParser::CPUStates::kIdle_] + 
                    this->prevCPUvalues[LinuxParser::CPUStates::kIOwait_];
    int Idle =  currCPUvalues[LinuxParser::CPUStates::kIdle_] + 
                currCPUvalues[LinuxParser::CPUStates::kIOwait_];

    // PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
    // NonIdle = user + nice + system + irq + softirq + steal
    int PrevNonIdle =   this->prevCPUvalues[LinuxParser::CPUStates::kUser_] +
                        this->prevCPUvalues[LinuxParser::CPUStates::kNice_] +
                        this->prevCPUvalues[LinuxParser::CPUStates::kSystem_] +
                        this->prevCPUvalues[LinuxParser::CPUStates::kIRQ_] +
                        this->prevCPUvalues[LinuxParser::CPUStates::kSoftIRQ_] +
                        this->prevCPUvalues[LinuxParser::CPUStates::kSteal_];
    int NonIdle =       currCPUvalues[LinuxParser::CPUStates::kUser_] + 
                        currCPUvalues[LinuxParser::CPUStates::kNice_] +
                        currCPUvalues[LinuxParser::CPUStates::kSystem_] +
                        currCPUvalues[LinuxParser::CPUStates::kIRQ_] +
                        currCPUvalues[LinuxParser::CPUStates::kSoftIRQ_] +
                        currCPUvalues[LinuxParser::CPUStates::kSteal_];

    // PrevTotal = PrevIdle + PrevNonIdle
    // Total = Idle + NonIdle
    int PrevTotal = PrevIdle + PrevNonIdle;
    int Total = Idle + NonIdle;

    // differentiate: actual value minus the previous one
    // totald = Total - PrevTotal
    // idled = Idle - PrevIdle
    float totald = Total - PrevTotal;
    totald == 0 ? totald = 1 : totald;     // make sure we don't divide by zero
    float idled = Idle - PrevIdle;
    float CPU_Percentage = (totald - idled)/ totald;

    // Save currCPUvalues as prevCPUvalues
    this->prevCPUvalues = currCPUvalues;
    return CPU_Percentage;
}