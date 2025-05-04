#ifndef QUIZ_H
#define QUIZ_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::ostream;

struct Answer {
    string text;
    int mechScore, electricalScore, civilScore, csScore, chemScore; //0-5 scores
    public:
        Answer() : text(""), mechScore(0), electricalScore(0), civilScore(0), csScore(0), chemScore(0) {}
        Answer(const string& text, int mech, int elec, int civ, int cs, int chem) : text(text), mechScore(mech), electricalScore(elec), civilScore(civ), csScore(cs), chemScore(chem) {}
};

class Question {
    public:
        static const int possAnswers = 5;
        string prompt;
        using collectionType = vector<Answer>;
        collectionType answers;
    public:
        class QuestionBuilder {
            private:
                string _prompt;
                collectionType _answers;
                using answerNumType = int;
                answerNumType answerNum = 0;
            public:
                QuestionBuilder& prompt(const string& prompt) {
                    _prompt = prompt;
                    return *this;
                };
                QuestionBuilder& addAnswer(const Answer& ans) {
                    _answers.push_back( ans);
                    return *this;
                }
                Question build() {
                    Question q;
                    q.prompt = _prompt;
                    q.answers = _answers;
                    return q;
                }
        };
        static QuestionBuilder builder()  { return QuestionBuilder(); }
        friend class QuestionBuilder;
};

class Quiz {
    private:
        int mechScore, electricalScore, civilScore, csScore, chemScore;
        string recommendedMajor;
        string quizName;
        using collectionType = vector<Question>;
        collectionType questionBank;
        using questionNumType = int;
    public:
        void addQuestion(const Question& q) { questionBank.push_back(q); }
        void displayQuestion(questionNumType, ostream&) const;
        void displayResults(ostream&) const;
        void refresh();
        //TODO: will need to accept question results
};

#endif