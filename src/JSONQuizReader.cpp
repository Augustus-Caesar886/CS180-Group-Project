#include "../header/JSONQuizReader.h"

using json = nlohmann::json;
using std::istream;

JSONQuizReader::JSONQuizReader(istream& input) {
    json quizData = json::parse(input);

    auto allQuestionData = quizData["questions"]; //Get MCQs
    for(int i = 0; i < allQuestionData.size(); ++i) {
        auto currQuestion = allQuestionData.at(i)["question" + std::to_string(i+1)];
        auto questionBuilder = Question::builder().prompt(currQuestion["prompt"]);
        for(unsigned j = 0; j < 5; ++j) {
            auto currAnswerData = currQuestion["answer" + std::to_string(j+1)];
            auto currAnswerScores = currAnswerData["scores"];
            questionBuilder.addAnswer(Answer(currAnswerData["text"], currAnswerScores["mechanical"], currAnswerScores["electrical"], currAnswerScores["civil"], currAnswerScores["compsci"], currAnswerScores["chemical"]));
        }
        quiz.addQuestion(questionBuilder.build());
    }

    auto frqQuestionPrompts = quizData["Free Response Prompts"]; //Get FRQ prompts
    for(int i = 0; i < frqQuestionPrompts.size(); ++i) {
        auto currQuestion = frqQuestionPrompts.at(i);
        
        quiz.addFRQQuestion(currQuestion);
    }
}