#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>

std::vector<int> stringValuesToInt(std::vector<std::string> CPUvalues);

class Processor {
 public:
  float Utilization();  // DONE: See src/processor.cpp
  Processor();          // Constructor

  // DONE: Declare any necessary private members
 private:
    std::vector<int> prevCPUvalues;
};

#endif