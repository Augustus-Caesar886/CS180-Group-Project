#ifndef COMMUNICABLE_PROCESS_H
#define COMMUNICABLE_PROCESS_H

#include <string>
using std::string;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <vector>
using std::vector;


class CommunicableProcess { 
    private:
        string path;
        string programName;
    public:
        CommunicableProcess(const string& filepath, const string& programName) : path(filepath), programName(programName) {}
        string query(const string&) const;

};

#endif