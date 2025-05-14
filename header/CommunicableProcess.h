#ifndef COMMUNICABLE_PROCESS_H
#define COMMUNICABLE_PROCESS_H

#include <string>
using std::string;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <unistd.h>

class CommunicableProcess {
    private:
        pid_t childPid;
        ifstream* readableLine = nullptr;
        ofstream* writeableLine = nullptr;
        size_t currReadableSize = 0;
        string getChildToParentLineFileName() const { return std::to_string(childPid) + "_to_" + std::to_string(getpid()); }
        string getParentToChildLineFileName() const { return std::to_string(getpid()) + "_to_" + std::to_string(childPid); }
    public:
        ~CommunicableProcess();
        CommunicableProcess(const string& filepath, const string& command);
        void send(const string&);
        string read();

};

#endif