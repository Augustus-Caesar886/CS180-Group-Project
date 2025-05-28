#include "../header/Quiz.h"
#include "../header/CommunicableProcess.h"

using std::endl;

void Quiz::displayQuestion(Quiz::questionNumType questionNum, ostream& out) const {
    if(questionNum <= questionBank.size()) {
        out << questionBank.at(questionNum-1).prompt << endl;
        char answerOption = 'a';
        for(int i = 0;i < Question::possAnswers; ++i) {
            out << "\t" << (answerOption++) << ". " << questionBank.at(questionNum-1).answers[i].text << endl;
        }
    } else {
        out << frqQuestions.at(questionNum - questionBank.size() - 1) << endl;
    }
}

void Quiz::displayResults(ostream& out) const {
    out << "Suggested major: " << getRecommendation() << endl;
    out << "Scores:" << endl;
    out << "\tMechanical Engineering: " << mechScore << "/" << maxMechScore() << endl; //TODO: Out of max possible points
    out << "\tElectrical Engineering: " << electricalScore << "/" << maxElectricalScore() << endl;
    out << "\tCivil Engineering: " << civilScore << "/" << maxCivilScore() << endl;
    out << "\tComputer Science: " << csScore << "/" << maxCSScore() << endl;
    out << "\tChemical Engineering: " << chemScore << "/" << maxChemScore() << endl;
}

void Quiz::acceptQuestionResponse(questionNumType quizNum, const string& response) {
    if(quizNum <= questionBank.size()) {
        char responseOption = response[0];
        Answer* ans = nullptr;
        switch(responseOption) { //Get the Answer
            case 'a':
                ans = &questionBank.at(quizNum-1).answers.at(0);
                break;
            case 'b':
                ans = &questionBank.at(quizNum-1).answers.at(1);
                break;
            case 'c':
                ans = &questionBank.at(quizNum-1).answers.at(2);
                break;
            case 'd':
                ans = &questionBank.at(quizNum-1).answers.at(3);
                break;
            case 'e':
                ans = &questionBank.at(quizNum-1).answers.at(4);
                break;
            default:

                break;
        } //Update scores
        mechScore += ans->mechScore;
        electricalScore += ans->electricalScore;
        civilScore += ans->civilScore;
        csScore += ans->csScore;
        chemScore += ans->chemScore;
    } else { //FRQ
        string pythonLocation = "";
        #ifdef __APPLE__ && __MACH__
            pythonLocation = "/Library/Frameworks/Python.framework/Versions/3.12/bin/python3";
        #elif __linux__
            pythonLocation = "/usr/bin/python3";
        #endif
        CommunicableProcess python3(pythonLocation, "python3.12");

        string result = python3.query("FRQLLM.py " + response);
        if(result == "Mechanical Engineering") {
            mechScore += 5;
        } else if (result == "Electrical Engineering") {
            electricalScore += 5;
        } else if (result == "Civil Engineering") {
            civilScore += 5;
        } else if (result == "Computer Science") {
            csScore += 5;
        } else if (result == "Chemical Engineering") {
            chemScore += 5;
        }
    }
}

double Quiz::getPercentage(double input1, double input2) const {
    if(input2 == 0) return 0;
    return input1 / input2;
}

string Quiz::getRecommendation() const {
    double percentages[Question::possAnswers] = { getPercentage(mechScore, maxMechScore()), 
                            getPercentage(electricalScore, maxElectricalScore()),
                            getPercentage(civilScore, maxCivilScore()),
                            getPercentage(csScore, maxCSScore()),
                            getPercentage(chemScore, maxChemScore())
    };
    bool allZero = true;
    for(unsigned i = 0; i < Question::possAnswers; ++i) { //Check if all max scores are 0
        if(percentages[i] != 0) {
            allZero = false;
            break;
        }
    }
    if(allZero) return "Undeclared";
    string majors[Question::possAnswers] = {
        "Mechanical Engineering",
        "Electrical Engineering",
        "Civil Engineering",
        "Computer Science",
        "Chemical Engineering",
    };
    int bestIndex = 0;
    for(unsigned i = 0; i < Question::possAnswers; ++i) {
        if(percentages[i] > percentages[bestIndex]) bestIndex = i;
    }
    return majors[bestIndex];
}

void Quiz::refresh() {
    mechScore = electricalScore = civilScore = csScore = chemScore = 0;
}

int Quiz::maxScore(int (*getScore)(const Answer& a)) const {
    int sum = 0;
    for(auto it : questionBank) {
        int candidate = 0;
        for(unsigned i = 0; i < Question::possAnswers; ++i) {
            candidate = std::max(candidate, getScore(it.answers[i]));
        }
        sum += candidate;
    }
    return sum + 5 * frqQuestions.size();
}

int Quiz::maxMechScore() const {
    return maxScore([](const Answer& a){
        return a.mechScore;
    });
}

int Quiz::maxElectricalScore() const {
    return maxScore([](const Answer& a){
        return a.electricalScore;
    });
}

int Quiz::maxCivilScore() const {
    return maxScore([](const Answer& a){
        return a.civilScore;
    });
}

int Quiz::maxCSScore() const {
    return maxScore([](const Answer& a){
        return a.csScore;
    });
}

int Quiz::maxChemScore() const {
    return maxScore([](const Answer& a){
        return a.chemScore;
    });
}
