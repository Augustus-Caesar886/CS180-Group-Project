import React from 'react';
import { useLocation, useNavigate } from 'react-router-dom';

function StudentMenuPage() {
  const location = useLocation();
  const navigate = useNavigate();
  const username = location.state?.username || 'Student';
  const savedAnswers = JSON.parse(localStorage.getItem('quizAnswers'));

  const handleTakeQuiz = () => {
    navigate('/quiz', { state: { username } });
  };

  const handleViewResults = () => {
    navigate('/result', { state: { username } });
  };

  const handleLogout = () => {
    navigate('/');
  };

  return (
    <div style={{
      padding: '2rem',
      backgroundColor: '#eef3ff',
      borderRadius: '12px',
      maxWidth: '600px',
      margin: '2rem auto',
      boxShadow: '0 4px 12px rgba(0, 0, 0, 0.1)',
      fontFamily: 'Arial, sans-serif',
      textAlign: 'center',
      color: '#333'
    }}>
      <h2 style={{ color: '#2b3a67', fontSize: '1.8rem', marginBottom: '1.5rem' }}>
        Welcome, {username} <span style={{ fontWeight: 'normal' }}>(Student)</span>
      </h2>

      <button
        onClick={handleTakeQuiz}
        style={{
          padding: '0.6rem 1.2rem',
          fontSize: '1rem',
          marginBottom: '1rem',
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
        Take Quiz
      </button>

      <br />

      {savedAnswers ? (
        <button
          onClick={handleViewResults}
          style={{
            padding: '0.6rem 1.2rem',
            fontSize: '1rem',
            marginTop: '0.5rem',
            backgroundColor: '#00b894',
            color: 'white',
            border: 'none',
            borderRadius: '8px',
            cursor: 'pointer',
            transition: 'background-color 0.2s ease'
          }}
          onMouseOver={e => e.target.style.backgroundColor = '#019875'}
          onMouseOut={e => e.target.style.backgroundColor = '#00b894'}
        >
          View Results
        </button>
      ) : (
        <p style={{ marginTop: '1rem', color: '#666' }}>
          You haven't taken the quiz yet.
        </p>
      )}

      <br /><br />

      <button
        onClick={handleLogout}
        style={{
          padding: '0.5rem 1.1rem',
          fontSize: '0.95rem',
          backgroundColor: '#d63031',
          color: 'white',
          border: 'none',
          borderRadius: '8px',
          cursor: 'pointer',
          transition: 'background-color 0.2s ease'
        }}
        onMouseOver={e => e.target.style.backgroundColor = '#b02121'}
        onMouseOut={e => e.target.style.backgroundColor = '#d63031'}
      >
        Log Out
      </button>
    </div>
  );
}

export default StudentMenuPage;
