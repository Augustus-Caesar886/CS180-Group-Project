import React, { useEffect, useState } from 'react';
import { useLocation, useNavigate } from 'react-router-dom'; // allows changing pages

function QuizResultsPage() {
  const location = useLocation();
  const navigate = useNavigate();

  const username = location.state?.username || 'Student'; // tries to get username from location state and defaults to student

  // Make answers and major stateful so we can set them in useEffect
  const [answers, setAnswers] = useState(location.state?.answers || []); // tries to get quiz answers from previous page's state
  const [major, setMajor] = useState(location.state?.major || null); // gets recommended major from state

  useEffect(() => {
    if ((!answers || answers.length === 0) && username) { // if there are answers saves, so if the quiz has been taken
      const storedAnswers = localStorage.getItem(`quizAnswers`); // get saved answers from localStorage
      if (storedAnswers) { // if there is data
        const parsedAnswers = JSON.parse(storedAnswers); // parse from json string to javascript array
        setAnswers(parsedAnswers); // update state with answers
        
        fetch('http://localhost:8080/quiz/recommendation')
          .then(res => res.json())
          .then(data=> {
            const recommendedMajor = data.recommendedMajor;
            setMajor({
            name: recommendedMajor,
            description: `Your interests align with ${recommendedMajor}.`,
            careers: [],
          });

        return fetch('http://localhost:8080/updateMajor', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({username, major: recommendedMajor}),
        });
      })
        .then(res => res?.json?.()) //once done fetching, then take apart into JS object 
        .then(data => {          // then output error if didn't return 'success'
          if(data.status !== 'success'){
            console.error('Major update failed:', data?.message);
          }
        })
        .catch(e => {
          console.error('Error getting recommendation or updating major:', e);
        });
      }
    }
  }, []);
  
  const handleGoBack = () => {
    navigate('/student', { state: { username } }); // sends user back to student menu
  };

  return (
    <div style={{ padding: '2rem' }}>
      <h2>Quiz Results</h2>

      {!answers || answers.length === 0 ? (
        <p>You haven't taken the quiz yet.</p>
      ) : (
        <>
          <p>Thanks for completing the quiz, {username}!</p>

          {major?.name && (
            <div>
              <h3>Recommended Major: {major.name}</h3>
              <p>{major.description}</p>
              <strong>Career Paths:</strong>
              <ul>
                {(major.careers || []).map((career, idx) => (
                  <li key={idx}>{career}</li>
                ))}
              </ul>
            </div>
          )}

          <br />
          <button onClick={handleGoBack}>Back to Menu</button>
        </>
      )}
    </div>
  );
}

export default QuizResultsPage;
