#ifndef COMMUNICABLE_PROCESS_H
#define COMMUNICABLE_PROCESS_H

#include <string>
using std::string;

#include <fstream>
using std::ifstream;
using std::ofstream;

class CommunicableProcess {
    private:
        pid_t childPid;
        ifstream* readableLine = nullptr;
        ofstream* writeableLine = nullptr;
    public:
        ~CommunicableProcess();
        CommunicableProcess(const string& filepath, const string& command);
        void send(const string&);
        string read();

};

#endif