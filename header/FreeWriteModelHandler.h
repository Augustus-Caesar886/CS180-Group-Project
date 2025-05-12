#ifndef FREE_WRITE_MODEL_HANDLER_H
#define FREE_WRITE_MODEL_HANDLER_H

#include "FreeWriteHandler.h"
#include <fstream>

using std::ifstream;
using std::ofstream;

class FreeWriteModelHandler : public FreeWriteHandler { //Singleton design pattern
    private:
    
    public:
        string getRecommendation(const string&) const;
};

#endif