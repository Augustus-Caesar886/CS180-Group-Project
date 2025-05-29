import React, { useState } from 'react';
import { useLocation, useNavigate } from 'react-router-dom';

function QuizMenuPage() {
  const { username } = useLocation().state || {};
  const navigate = useNavigate();

  const questions = [
    { question: "Favorite subject?", options: ["Math", "Physics", "Chemistry", "Biology", "Writing", "Arts"] },
    { question: "Do you prefer working alone or in a team?", options: ["Alone", "In a team", "Both"] },
  ];
  const majorOptions = [
    { name: "Mechanical Engineering", description: "...", careers: [] },
    { name: "Computer Engineering", description: "...", careers: [] },
  ];

  const [currentQuestionIndex, setCurrentQuestionIndex] = useState(0);
  const [answers, setAnswers] = useState(
    JSON.parse(localStorage.getItem('quizAnswers')) || Array(questions.length).fill(null)
  );

  const handleAnswerChange = (e) => {
    const newA = [...answers];
    newA[currentQuestionIndex] = e.target.value;
    setAnswers(newA);
    localStorage.setItem('quizAnswers', JSON.stringify(newA));
  };

  const determineMajor = (ans) => {
    const score = ans.reduce((acc, a) => acc + (['Math','Physics'].includes(a) ? 1 : 0), 0);
    return score >= 2 ? majorOptions[1] : majorOptions[0];
  };

  const handleNext = () => {
    if (currentQuestionIndex < questions.length - 1) {
      setCurrentQuestionIndex(i => i + 1);
    } else {
      const chosenMajor = determineMajor(answers);

      const users = JSON.parse(localStorage.getItem('users')) || [];
      const user = users.find(u => u.username === username);
      if (user && user.studentCode) {
        const classes = JSON.parse(localStorage.getItem('classrooms')) || [];
        const cls = classes.find(c => c.code === user.studentCode);
        if (cls) {
          const stu = cls.students.find(s => s.username === username);
          if (stu) {
            stu.major = chosenMajor.name;
            localStorage.setItem('classrooms', JSON.stringify(classes));
          }
        }
      }

      navigate('/result', {
        state: { username, answers, major: chosenMajor }
      });
    }
  };

  const q = questions[currentQuestionIndex];
  return (
    <div style={{
      padding: '2rem',
      backgroundColor: '#f5f7ff',
      borderRadius: '12px',
      maxWidth: '600px',
      margin: '2rem auto',
      boxShadow: '0 4px 10px rgba(0, 0, 0, 0.1)',
      fontFamily: 'Arial, sans-serif',
      color: '#333'
    }}>
      <h2 style={{ fontSize: '1.5rem', marginBottom: '1rem', color: '#2b3a67' }}>
        Quiz for {username}
      </h2>
      <p style={{ fontWeight: 'bold', marginBottom: '1rem' }}>{q.question}</p>
      {q.options.map((opt, i) => (
        <div key={i} style={{ marginBottom: '0.5rem' }}>
          <input
            type="radio"
            name="ans"
            value={opt}
            checked={answers[currentQuestionIndex] === opt}
            onChange={handleAnswerChange}
            style={{ marginRight: '0.5rem' }}
          />
          <label>{opt}</label>
        </div>
      ))}
      <button
        onClick={handleNext}
        style={{
          marginTop: '1rem',
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
        {currentQuestionIndex < questions.length - 1 ? 'Next' : 'Finish'}
      </button>
    </div>
  );
}

export default QuizMenuPage;
