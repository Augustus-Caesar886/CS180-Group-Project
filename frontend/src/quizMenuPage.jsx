import React, { useEffect, useState } from 'react';
import { useLocation, useNavigate } from 'react-router-dom';

function QuizMenuPage() {
  const { username } = useLocation().state || {};
  const navigate = useNavigate();

  const [currentQuestionIndex, setCurrentQuestionIndex] = useState(0);
  const [questionData, setQuestionData] = useState(null);
  const [selectedAnswer, setSelectedAnswer] = useState("");
  
  useEffect(() => {
    fetch(`http://localhost:8080/quiz/question/${currentQuestionIndex}`)
    .then(res => res.json())
    .then(data => setQuestionData(data))
    .catch(err => console.error("Error fetching question:", err));
  }, [currentQuestionIndex]);

  const handleSubmitAnswer = () => {
    if(!selectedAnswer){return;}

    fetch('http://localhost:8080/quiz/answer',{
      method: 'POST',
      headers: { 'Content-Type': 'application/json'},
      body: JSON.stringify({
        questionIndex: currentQuestionIndex,
        answerChoice: selectedAnswer
      })
    })
    .then(res => {
      if(!res.ok){throw new Error("Failed to submit answer");}
      if(currentQuestionIndex < 18){
        setCurrentQuestionIndex(prev => prev + 1);
        setSelectedAnswer("");
      }else{
        fetch('http://localhost:8080/quiz/recommendation')
          .then(res => res.json())
          .then(data => {
            const major = data.recommendedMajor;
            navigate('/result', {state: {username, major}});
          });
      }
    })
    .catch(err =>{
      console.error("Error submitting answer:", err);
      alert("There was a problem submitting your answer.");
    });
  };

  return (
    <div style={{ padding: '2rem' }}>
      <h2>Quiz for {username}</h2>

      {questionData ? (
        <>
          <p><strong>Question {currentQuestionIndex + 1}:</strong> {questionData.prompt}</p>

           {questionData.type === "mcq" && questionData.answers.map((opt, i) => {
            const letter = String.fromCharCode(97 + i);
            return (
              <div key={i}>
                <input
                  type="radio"
                  name="ans"
                  value={letter}
                  checked={selectedAnswer === letter}
                  onChange={(e) => setSelectedAnswer(e.target.value)}
                />
                <label>{opt}</label>
              </div>
            );
          })}

          {questionData.type === "frq" && (
            <div>
              <textarea
                placeholder="Your response..."
                value={selectedAnswer}
                onChange={(e) => setSelectedAnswer(e.target.value)}
                rows={4}
                cols={60}
              />
            </div>
          )}

          <button onClick={handleSubmitAnswer} style={{ marginTop: '1rem' }}>
            {currentQuestionIndex < 18 ? 'Next' : 'Finish'}
          </button>
        </>
      ) : (
        <p>Loading question...</p>
      )}
    </div>
  );
}

export default QuizMenuPage;