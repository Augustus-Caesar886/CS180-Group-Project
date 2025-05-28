#include "../header/Quiz.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::InSequence;

#include <sstream>
using std::ostringstream;

const bool enableFRQTests = false;

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
    quiz.displayQuestion(2, testOutput); //issue
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

TEST(QuizTests, testAcceptResponse) {
    Question q1 = Question::builder().prompt("What activity sounds the most fun to you?")
        .addAnswer(Answer("Designing a robot to play soccer", 5, 0, 0, 0, 0))
        .addAnswer(Answer("Creating a circuit to power a lightbulb", 0, 5, 0, 0, 0))
        .addAnswer(Answer("Drawing a city map with roads and bridges", 0, 0, 5, 0, 0))
        .addAnswer(Answer("Creating a chatbot", 0, 0, 0, 5, 0))
        .addAnswer(Answer("Making a new cleaning product to remove any stain", 0, 0, 0, 0, 5))
    .build();

    Quiz q;
    q.addQuestion(q1);
    q.acceptQuestionResponse(1, "a");
    EXPECT_EQ(q.getRecommendation(), "Mechanical Engineering");

    if(enableFRQTests) {
        q.refresh();
        q.addFRQQuestion("What are your hobbies?");
        q.acceptQuestionResponse(2, "Programming");
        EXPECT_EQ(q.getRecommendation(), "Computer Science");
    }
}

TEST(QuizTests, testRefresh) {
    Question q1 = Question::builder().prompt("What activity sounds the most fun to you?")
        .addAnswer(Answer("Designing a robot to play soccer", 5, 0, 0, 0, 0))
        .addAnswer(Answer("Creating a circuit to power a lightbulb", 0, 5, 0, 0, 0))
        .addAnswer(Answer("Drawing a city map with roads and bridges", 0, 0, 5, 0, 0))
        .addAnswer(Answer("Creating a chatbot", 0, 0, 0, 5, 0))
        .addAnswer(Answer("Making a new cleaning product to remove any stain", 0, 0, 0, 0, 5))
    .build();

    Quiz q;
    q.addQuestion(q1);
    q.acceptQuestionResponse(1, "a");
    q.refresh();
    EXPECT_EQ(q.getRecommendation(), "Undeclared");
}

TEST(QuizTests, testRecommend) {
    Question q1 = Question::builder().prompt("What activity sounds the most fun to you?")
        .addAnswer(Answer("Designing a robot to play soccer", 1, 0, 0, 0, 0)) //0 points to any category
        .addAnswer(Answer("Creating a circuit to power a lightbulb", 0, 0, 0, 0, 0))
        .addAnswer(Answer("Drawing a city map with roads and bridges", 0, 0, 1, 0, 0))
        .addAnswer(Answer("Creating a chatbot", 0, 0, 0, 1, 0))
        .addAnswer(Answer("Making a new cleaning product to remove any stain", 0, 0, 0, 0, 1))
    .build();
    Question q2 = Question::builder().prompt("Your friend wants help with a school project. What would you most enjoy helping them with?")
        .addAnswer(Answer("Building a rocket that actually launches", 1, 0, 0, 0, 0))
        .addAnswer(Answer("Setting up LEDs on a microcontroller", 1, 1, 0, 0, 0)) //gives 1 point to 2 categories
        .addAnswer(Answer("Making a 3D interactive map of a city", 0, 0, 1, 0, 0))
        .addAnswer(Answer("Programming a simple game on a tablet", 0, 0, 0, 1, 0))
        .addAnswer(Answer("Creating any science experiment with materials", 0, 0, 0, 0, 1))
    .build();

    Quiz q;
    q.addQuestion(q1);
    q.addQuestion(q2);
    q.acceptQuestionResponse(2, "b");
    EXPECT_EQ(q.getRecommendation(), "Electrical Engineering"); // 1/1 points compared to 1/2 points for ME

    q.refresh();
    EXPECT_EQ(q.getRecommendation(), "Undeclared"); //Default recommendation
}

TEST(QuizTests, testLongResponse) {
    if(enableFRQTests) {
        string response = "If I had to describe myself in a few words, I’d say I’m curious, driven, and always building something—whether it’s a piece of code, a new skill, or a deeper understanding of the world around me. I’ve always been the kind of person who likes figuring out how things work. That’s what drew me to computer science: the idea that I could use logic and creativity to build things that actually do something. But beyond coding and school, I’m someone who values growth. I’m constantly trying to push myself out of my comfort zone, whether that means leading a team in a group project, teaching myself a new programming language, or even just asking better questions in class. I care a lot about being reliable and honest—if I say I’m going to do something, I’ll do it, and I try to be the kind of person others can count on. I’m also really interested in people. I love learning about different perspectives, especially when it comes to how technology affects our lives. Someday, I hope to use what I learn in computer science to solve problems that matter—whether that’s improving access to education, protecting digital privacy, or creating tools that make everyday life easier. In short, I’m a learner, a builder, and someone who wants to make a meaningful impact. I may not have all the answers yet, but I’m excited to keep exploring until I find them.";
        Quiz q;
        q.addFRQQuestion("Write a short essay about who you are as a person.");
        q.acceptQuestionResponse(1, response);
        EXPECT_EQ(q.getRecommendation(), "Computer Science");
    }
}