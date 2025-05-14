#include "../header/JSONQuizReader.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::InSequence;

#include <fstream>
using std::ifstream;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

const bool manualApproval = false;

TEST(JSONQuizReaderTests, testReader) {
    ifstream quizFile("quiz.json");
    ASSERT_TRUE(quizFile.is_open());
    Quiz q = JSONQuizReader(quizFile).getQuiz();
    quizFile.close();

    if(manualApproval) {
        q.displayQuestion(1, cout);    
        string manualApproval = "";
        cout << endl << "Is the above result correct for question 1? (y/n)" << endl;
        cin >> manualApproval;
        EXPECT_EQ(manualApproval, "y");
    }
}