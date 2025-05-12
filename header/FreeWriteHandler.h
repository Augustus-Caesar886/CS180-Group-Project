#ifndef FREE_WRITE_HANDLER_H
#define FREE_WRITE_HANDLER_H

#include <string>
using std::string;

class FreeWriteHandler { //Singleton design pattern
    public:
        virtual string getRecommendation(const string&) const = 0;
};

#endif