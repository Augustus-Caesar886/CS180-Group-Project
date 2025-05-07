import { useLocation, useNavigate } from 'react-router-dom'; // allows changing pages
import React, { useState } from 'react' // core react library and usestate to manage state, like which question user is on

function QuizMenuPage() { // functional component
    const location = useLocation(); // returns location object of current page of app, used to access state passed from previous page
    const navigate = useNavigate(); // used to go to a different page after quiz is completed, changes current route in app
    const username = location.state?.username || 'Student'; // access username from location state, fallback value is 'Student'
// question list
    const questions = [
        {
        question: "Favorite subject?",
        options: ["Math", "Physics", "Chemistry", "Biology", "Writing", "Arts"],
        answer: null, // initially null, will store user response
        },
        {
        question: "Do you prefer working alone or in a team?",
        options: ["Alone", "In a team", "Both"],
        answer: null
        }
    ];
    const majorOptions = [
        {
          name: "Mechanical Engineering",
          description: "Mechanical Engineering focuses on the design and development of machines and mechanical systems.",
          careers: ["Mechanical Engineer", "Product Designer", "Automotive Engineer"]
        },
        {
          name: "Computer Engineering",
          description: "Computer Engineering combines computer science and electrical engineering to design and develop computer systems and hardware-software integration.",
          careers: ["Software Developer", "Embedded Systems Engineer", "Hardware Engineer"]
        }
      ];

    // set up state for tracking quiz state
    const [currentQuestionIndex, setCurrentQuestionIndex] = useState(0); // state variable to track which question the user is answering
    const [answer, setAnswers] = useState(Array(questions.length).fill(null)); // creates state variable answer which is an array, all values are null until user answers

    // function called when user selects answer to update the state of the selected answer in the quiz when the user selects a different one
    // called when radio button <input type="radio"> is clicked
    const handleAnswerChange = (event) => {
        const newAnswers = [...answer]; // makes copy of answer array
        newAnswers[currentQuestionIndex] = event.target.value; // updates the answer for the current question
        setAnswers(newAnswers); // sets new answers array into the state so re-renders component to reflect current state
    }

    // handles moving to next question or finishing state
    const handleNextQuestion = () => {
        if (currentQuestionIndex < questions.length - 1) {
            setCurrentQuestionIndex(currentQuestionIndex + 1);
        } else {
            const defaultMajor = majorOptions[0]
            
            navigate('/result', {
                state: {
                    username,
                    answers: answer,
                    major: defaultMajor
                }
            });
        }
    };
  const currentQuestion = questions[currentQuestionIndex]; // retrieves question object corresponding to question index

  return (
    <div style={{ padding: '2rem' }}>
      <h2>Welcome, {username}</h2> {/* display greeting*/}
      <h3>Engineering Major Quiz</h3> {/* display quiz title */}

      {/* display current question */}
      <p>{currentQuestion.question}</p>

      {/* loop through options array to display answer choices*/}
      {currentQuestion.options.map((option, index) => (
        <div key={index}>
          <input
            type="radio"
            id={option}
            name="answer"
            value={option}
            checked={answer[currentQuestionIndex] === option}
            onChange={handleAnswerChange}
          />
          <label htmlFor={option}>{option}</label> {/* display label for current option */}
        </div>
      ))}

      <br />
      <button onClick={handleNextQuestion}> {/* move to next question or finish quiz */}
        {currentQuestionIndex < questions.length - 1 ? "Next Question" : "Finish Quiz"} {/* button text changes depending on question progrssion */}
      </button>
    </div>
  );
}

export default QuizMenuPage;
