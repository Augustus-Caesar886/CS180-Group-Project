#ifndef QUIZ_READER_H
#define QUIZ_READER_H

#include "json.hpp"
#include "Quiz.h"
#include <iostream>

using std::istream;
using json = nlohmann::json;

class JSONQuizReader {
    private:
        Quiz quiz;
    public:
        JSONQuizReader(istream&);
        Quiz getQuiz() const { return quiz; }
};

#endif