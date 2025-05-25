#include "../header/Quiz.h"

using std::endl;

void Quiz::displayQuestion(Quiz::questionNumType questionNum, ostream& out) const {
    out << questionBank.at(questionNum-1).prompt << endl;
    char answerOption = 'a';
    for(int i = 0;i < Question::possAnswers; ++i) {
        out << "\t" << (answerOption++) << ". " << questionBank.at(questionNum-1).answers[i].text << endl;
    }
}
void Quiz::displayResults(ostream& out) const {
    out << "Suggested major: " << recommendedMajor << endl;
    out << "Scores:" << endl;
    out << "\tMechanical Engineering: " << mechScore << endl; //TODO: Out of max possible points
    out << "\tElectrical Engineering: " << electricalScore << endl;
    out << "\tCivil Engineering: " << civilScore << endl;
    out << "\tComputer Science: " << csScore << endl;
    out << "\tChemical Engineering: " << chemScore << endl;
}

void Quiz::refresh() {
    //TODO: implement
}