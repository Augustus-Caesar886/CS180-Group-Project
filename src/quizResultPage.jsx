import React from 'react';
import { useLocation, useNavigate } from 'react-router-dom'; // allows changing pages

function QuizResultsPage() { // functional component
    const location = useLocation(); // returns location object of current page of app, used to access state passed from previous page
    const navigate = useNavigate(); // used to go to different pages

    const username = location.state?.username || 'Student'; // access username from location state
    const answers = location.state?.answers || [];
    const major = location.state?.major;

    const handleGoBack = () => {
        navigate('/student', { state: { username }})
    };
    return (
        <div style={{ padding: '2rem' }}>
          <h2>Quiz Results</h2>
          <p>Thanks for completing the quiz, {username}!</p>
    
          <h3>Your Answers:</h3>
          <ul>
            {answers.map((answer, index) => (
              <li key={index}>Question {index + 1}: {answer || 'No answer given'}</li>
            ))}
          </ul>
    
          {major && (
            <div>
              <h3>Recommended Major: {major.name}</h3>
              <p>{major.description}</p>
              <strong>Career Paths:</strong>
              <ul>
                {major.careers.map((career, idx) => (
                  <li key={idx}>{career}</li>
                ))}
              </ul>
            </div>
          )}
    
          <br />
          <button onClick={handleGoBack}>Back to Menu</button>
        </div>
      );
    }
    
    export default QuizResultsPage;
