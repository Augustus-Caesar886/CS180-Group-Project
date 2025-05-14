#include "../header/CommunicableProcess.h"
#include <unistd.h>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>

using std::endl;
using std::getline;
using std::stringstream;
using std::string;
using std::vector;

CommunicableProcess::~CommunicableProcess() {
    if(readableLine != nullptr) {
        std::remove(getChildToParentLineFileName().c_str());
        readableLine->close();
        delete readableLine;
    }
    if(writeableLine != nullptr) {
        std::remove(getParentToChildLineFileName().c_str());
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

        stringstream command;
        string token = "";
        vector<string> parsed;

        while(command >> token) {
            parsed.push_back(token);
        } 
        char** argform = new char*[parsed.size()];

        int ret = execv(filepath.c_str(), argform); //TODO: parse commands 
        exit(1);
    } else if(childPid > 0) { //Parent
        writeableLine = new ofstream(std::to_string(parentPid) + "_to_" + std::to_string(childPid));
        readableLine = new ifstream(std::to_string(childPid) + "_to_" + std::to_string(parentPid));
        // Get the initial file size
        currReadableSize = 0;
    }
}
void CommunicableProcess::send(const string& message) {
    *writeableLine << message << endl;
}

#include <iostream>

string CommunicableProcess::read() {
    string ret = "";
    while(not readableLine->is_open()) {
        readableLine->open(getChildToParentLineFileName());
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    readableLine->seekg(0, std::ios::end);
    while(readableLine->tellg() != -1 and readableLine->tellg() <= currReadableSize) {
        readableLine->clear();
        readableLine->seekg(0, std::ios::end);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    readableLine->seekg(currReadableSize);
    getline(*readableLine, ret);
    currReadableSize = readableLine->tellg();
    
    return ret;
}