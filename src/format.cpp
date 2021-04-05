#include <string>

#include "format.h"

using std::string;
using std::to_string;

// we need something to fill in zeros in front of 
// single digits for the clock
string Format::Pad(string s, string pad) {
    if (s.size() == 1) {
        s.insert(0, pad);
    }
    return s;
}

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    int sec, min, hrs;
    min = seconds / 60;
    sec = seconds % 60;
    hrs = min / 60;
    min = min % 60;
    return Format::Pad(to_string(hrs), "0") + ':' + 
           Format::Pad(to_string(min), "0") + ':' + 
           Format::Pad(to_string(sec), "0"); 
}