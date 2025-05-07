#include "../header/Quiz.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::InSequence;

#include <sstream>
using std::ostringstream;

TEST(QuestionTests, testQuestion) {
    Question q1 = Question::builder().prompt("What activity sounds the most fun to you?")
        .addAnswer(Answer("Designing a robot to play soccer", 5, 0, 0, 0, 0))
        .addAnswer(Answer("Creating a circuit to power a lightbulb", 0, 5, 0, 0, 0))
        .addAnswer(Answer("Drawing a city map with roads and bridges", 0, 0, 5, 0, 0))
        .addAnswer(Answer("Creating a chatbot", 0, 0, 0, 5, 0))
        .addAnswer(Answer("Making a new cleaning product to remove any stain", 0, 0, 0, 0, 5))
    .build();

    EXPECT_EQ(q1.prompt, "What activity sounds the most fun to you?");
    EXPECT_EQ(q1.answers.size(), 5);
    EXPECT_EQ(q1.answers.at(2).text, "Drawing a city map with roads and bridges");
    EXPECT_EQ(q1.answers.at(2).civilScore, 5);
    EXPECT_EQ(q1.answers.at(2).csScore, 0);
}

TEST(QuizTests, testQuiz) {
    Question q1 = Question::builder().prompt("What activity sounds the most fun to you?")
        .addAnswer(Answer("Designing a robot to play soccer", 5, 0, 0, 0, 0))
        .addAnswer(Answer("Creating a circuit to power a lightbulb", 0, 5, 0, 0, 0))
        .addAnswer(Answer("Drawing a city map with roads and bridges", 0, 0, 5, 0, 0))
        .addAnswer(Answer("Creating a chatbot", 0, 0, 0, 5, 0))
        .addAnswer(Answer("Making a new cleaning product to remove any stain", 0, 0, 0, 0, 5))
    .build();
    Question q2 = Question::builder().prompt("Your friend wants help with a school project. What would you most enjoy helping them with?")
        .addAnswer(Answer("Building a rocket that actually launches", 5, 0, 0, 0, 0))
        .addAnswer(Answer("Setting up LEDs on a microcontroller", 0, 5, 0, 0, 0))
        .addAnswer(Answer("Making a 3D interactive map of a city", 0, 0, 5, 0, 0))
        .addAnswer(Answer("Programming a simple game on a tablet", 0, 0, 0, 5, 0))
        .addAnswer(Answer("Creating any science experiment with materials", 0, 0, 0, 0, 5))
    .build();

    ostringstream testOutput;
    
    Quiz quiz;
    quiz.addQuestion(q1);
    quiz.addQuestion(q2);
    quiz.displayQuestion(2, testOutput);
    EXPECT_EQ(testOutput.str(), 
        (string("Your friend wants help with a school project. What would you most enjoy helping them with?") + string("\n") +
            string("\ta. Building a rocket that actually launches") + string("\n") +
            string("\tb. Setting up LEDs on a microcontroller") + string("\n") +
            string("\tc. Making a 3D interactive map of a city") + string("\n") +
            string("\td. Programming a simple game on a tablet") + string("\n") +
            string("\te. Creating any science experiment with materials") + string("\n")
        )
    ); 
    //TODO: Update quiz tests when output posts scores
}

//TODO: Test quiz refresh 