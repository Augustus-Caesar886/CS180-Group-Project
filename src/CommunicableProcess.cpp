#include "../header/CommunicableProcess.h"
#include <unistd.h>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include <filesystem>

using std::endl;
using std::getline;
using std::stringstream;
using std::string;
using std::vector;
using std::fstream;

string CommunicableProcess::query(const string& msg) const {
    int pid = fork();
    if(pid == 0) { //Child, which will read the argument and output to file
        stringstream command(msg);
        string token = "";
        vector<string> parsed;
        while(command >> token) {
            parsed.push_back(token);
        } 
        const char **argv = new const char* [parsed.size()+2];
        argv[0] = programName.c_str();
        for(int i = 0; i < parsed.size(); ++i) {
            argv[i+1] = parsed.at(i).c_str();
        }
        argv[parsed.size()+1] = NULL;
        int ret = execv(path.c_str(), (char* const*)argv); 
        exit(ret);
    } else if(pid > 0) { //Parent, which will read the file then delete it
        while(not std::filesystem::exists("major.txt")) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        fstream f("major.txt");
        while(not f.is_open()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        string line = "";
        getline(f, line);
        std::remove("major.txt");
        return line;
    }
}