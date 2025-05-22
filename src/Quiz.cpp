#include "../header/Quiz.h"
#include "../header/CommunicableProcess.h"

using std::endl;

void Quiz::displayQuestion(Quiz::questionNumType questionNum, ostream& out) const {
    if(questionNum < questionBank.size()) {
        out << questionBank.at(questionNum-1).prompt << endl;
        char answerOption = 'a';
        for(int i = 0;i < Question::possAnswers; ++i) {
            out << "\t" << (answerOption++) << ". " << questionBank.at(questionNum-1).answers[i].text << endl;
        }
    } else {
        out << frqQuestions.at(questionNum - questionBank.size()) << endl;
    }
}

void Quiz::displayResults(ostream& out) const {
    out << "Suggested major: " << recommendedMajor << endl;
    out << "Scores:" << endl;
    out << "\tMechanical Engineering: " << mechScore << "/" << maxMechScore() << endl; //TODO: Out of max possible points
    out << "\tElectrical Engineering: " << electricalScore << "/" << maxElectricalScore() << endl;
    out << "\tCivil Engineering: " << civilScore << "/" << maxCivilScore() << endl;
    out << "\tComputer Science: " << csScore << "/" << maxCSScore() << endl;
    out << "\tChemical Engineering: " << chemScore << "/" << maxChemScore() << endl;
}

void Quiz::acceptQuestionResponse(questionNumType quizNum, const string& response) {
    if(quizNum < questionBank.size()) {
        char responseOption = response[0];
        switch(responseOption) {
            case 'a':
                const Answer& ans = questionBank.at(responseOption - '0').answers.at(0);
                mechScore += ans.mechScore;
                electricalScore += ans.electricalScore;
                civilScore += ans.civilScore;
                csScore += ans.csScore;
                chemScore += ans.chemScore;
                break;
            case 'b':
                const Answer& ans = questionBank.at(responseOption - '0').answers.at(1);
                mechScore += ans.mechScore;
                electricalScore += ans.electricalScore;
                civilScore += ans.civilScore;
                csScore += ans.csScore;
                chemScore += ans.chemScore;
                break;
            case 'c':
                const Answer& ans = questionBank.at(responseOption - '0').answers.at(2);
                mechScore += ans.mechScore;
                electricalScore += ans.electricalScore;
                civilScore += ans.civilScore;
                csScore += ans.csScore;
                chemScore += ans.chemScore;
                break;
            case 'd':
                const Answer& ans = questionBank.at(responseOption - '0').answers.at(3);
                mechScore += ans.mechScore;
                electricalScore += ans.electricalScore;
                civilScore += ans.civilScore;
                csScore += ans.csScore;
                chemScore += ans.chemScore;
                break;
            case 'e':
                const Answer& ans = questionBank.at(responseOption - '0').answers.at(4);
                mechScore += ans.mechScore;
                electricalScore += ans.electricalScore;
                civilScore += ans.civilScore;
                csScore += ans.csScore;
                chemScore += ans.chemScore;
                break;
            default:

                break;
        }
    } else { //FRQ
        string pythonLocation = "";
        #ifdef __APPLE__ && __MACH__
            pythonLocation = "/Library/Frameworks/Python.framework/Versions/3.12/bin/python3";
        #elif __linux__
            pythonLocation = "/usr/bin/python3";
        #endif
        CommunicableProcess python3(pythonLocation, "python3");

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

string Quiz::getRecommendation() const {

}

void Quiz::refresh() {
    mechScore = electricalScore = civilScore = csScore = chemScore = 0;
}

int Quiz::maxMechScore() const {

}

int Quiz::maxElectricalScore() const {

}

int Quiz::maxCivilScore() const {

}

int Quiz::maxCSScore() const {

}

int Quiz::maxChemScore() const {

}
