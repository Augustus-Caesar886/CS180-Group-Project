import React, { useEffect, useState } from 'react';
import { useLocation, useNavigate } from 'react-router-dom';

function QuizResultsPage() {
  const location = useLocation();
  const navigate = useNavigate();

  const username = location.state?.username || 'Student';

  const [answers, setAnswers] = useState(location.state?.answers || []);
  const [major, setMajor] = useState(location.state?.major || null);

  useEffect(() => {
    if ((!answers || answers.length === 0) && username) {
      const storedAnswers = localStorage.getItem(`quizAnswers`);
      if (storedAnswers) {
        const parsedAnswers = JSON.parse(storedAnswers);
        setAnswers(parsedAnswers);
        setMajor(determineMajor(parsedAnswers));
      }
    }
  }, []);

  function determineMajor(answers) {
    const score = answers.reduce((acc, answer) => {
      if (['Math', 'Physics'].includes(answer)) return acc + 1;
      return acc;
    }, 0);

    if (score >= 2) {
      return {
        name: "Computer Engineering",
        description:
          "You enjoy logical thinking, math, and hardware/software systems.",
        careers: [
          "Software Developer",
          "Embedded Systems Engineer",
          "Hardware Engineer",
        ],
      };
    } else {
      return {
        name: "Mechanical Engineering",
        description:
          "You enjoy building things and understanding mechanics.",
        careers: [
          "Mechanical Engineer",
          "Product Designer",
          "Automotive Engineer",
        ],
      };
    }
  }

  const handleGoBack = () => {
    navigate('/student', { state: { username } });
  };

  return (
    <div style={{
      padding: '2rem',
      backgroundColor: '#f5f7ff',
      borderRadius: '12px',
      maxWidth: '700px',
      margin: '2rem auto',
      boxShadow: '0 4px 10px rgba(0, 0, 0, 0.1)',
      fontFamily: 'Arial, sans-serif',
      color: '#333'
    }}>
      <h2 style={{ fontSize: '1.75rem', color: '#2b3a67', marginBottom: '1rem' }}>
        Quiz Results
      </h2>

      {!answers || answers.length === 0 ? (
        <p>You haven't taken the quiz yet.</p>
      ) : (
        <>
          <p style={{ marginBottom: '1rem' }}>
            Thanks for completing the quiz, <strong>{username}</strong>!
          </p>
          <h3 style={{ color: '#444', marginBottom: '0.5rem' }}>Your Answers:</h3>
          <ul style={{ paddingLeft: '1.5rem', marginBottom: '1rem' }}>
            {answers.map((answer, index) => (
              <li key={index} style={{ marginBottom: '0.25rem' }}>
                Question {index + 1}: {answer || 'No answer given'}
              </li>
            ))}
          </ul>

          {major && (
            <div style={{ marginTop: '1.5rem' }}>
              <h3 style={{ color: '#444', marginBottom: '0.5rem' }}>
                Recommended Major: <span style={{ color: '#4e63ea' }}>{major.name}</span>
              </h3>
              <p style={{ marginBottom: '0.5rem' }}>{major.description}</p>
              <strong>Career Paths:</strong>
              <ul style={{ paddingLeft: '1.5rem' }}>
                {major.careers.map((career, idx) => (
                  <li key={idx} style={{ marginBottom: '0.25rem' }}>{career}</li>
                ))}
              </ul>
            </div>
          )}

          <button
            onClick={handleGoBack}
            style={{
              marginTop: '2rem',
              padding: '0.5rem 1.5rem',
              fontSize: '1rem',
              backgroundColor: '#4e63ea',
              color: 'white',
              border: 'none',
              borderRadius: '8px',
              cursor: 'pointer',
              transition: 'background-color 0.2s ease'
            }}
            onMouseOver={e => e.target.style.backgroundColor = '#3a4dc4'}
            onMouseOut={e => e.target.style.backgroundColor = '#4e63ea'}
          >
            Back to Menu
          </button>
        </>
      )}
    </div>
  );
}

export default QuizResultsPage;
