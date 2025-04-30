#ifndef QUIZ_H
#define QUIZ_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::ostream;

struct Answer {
    int mechScore, electricalScore, civilScore, csScore, chemScore; //0-5 scores
};

class Question {
    private:
        string _prompt;
        Answer answers[5];
    public:
        //TODO: builder

};

class Quiz {
    private:
        int mechScore, electricalScore, civilScore, csScore, chemScore;
        string recommendedMajor;
        string quizName;
        using collectionType = vector<Question>;
        collectionType questionBank;
        using questionNum = int;
    public:
        void displayQuestion(ostream&) const;
        void displayResults(ostream&) const;
        void refresh();
};

#endif