#include "../header/CommunicableProcess.h"
#include <unistd.h>

using std::endl;
using std::getline;

CommunicableProcess::~CommunicableProcess() {
    if(readableLine != nullptr) {
        readableLine->close();
        delete readableLine;
    }
    if(writeableLine != nullptr) {
        writeableLine->close();
        delete writeableLine;
    }
}
CommunicableProcess::CommunicableProcess(const string& filepath, const string& command) {
    pid_t parentPid = getpid();
    childPid = fork();
    if(childPid == 0) { //Child
        pid_t myPid = getpid();
        string childToParentLineFileName = std::to_string(myPid) + "_to_" + std::to_string(parentPid);
        freopen(childToParentLineFileName.c_str(), "w", stdout);
        string parentToChildLineFileName = std::to_string(parentPid) + "_to_" + std::to_string(myPid);
        freopen(parentToChildLineFileName.c_str(), "r", stdin);
        int ret = execv(filepath.c_str(), command.c_str()); //TODO: parse commands 
        exit(1);
    } else if(childPid > 0) { //Parent
        writeableLine = new ofstream(std::to_string(parentPid) + "_to_" + std::to_string(childPid));
        readableLine = new ifstream(std::to_string(childPid) + "_to_" + std::to_string(parentPid));
    }
}
void CommunicableProcess::send(const string& message) {
    *writeableLine << message << endl;
}
string CommunicableProcess::read() {
    string ret = "";
    getline(*readableLine, ret);
    return ret;
}