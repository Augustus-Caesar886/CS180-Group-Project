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
    { name: "Mechanical Engineering", description: "...", careers: [/*…*/] },
    { name: "Computer Engineering", description: "...", careers: [/*…*/] },
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

      // 1️⃣ Update student major in classroom
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

      // 2️⃣ Navigate to result
      navigate('/result', {
        state: { username, answers, major: chosenMajor }
      });
    }
  };

  const q = questions[currentQuestionIndex];
  return (
    <div style={{ padding: '2rem' }}>
      <h2>Quiz for {username}</h2>
      <p>{q.question}</p>
      {q.options.map((opt,i) => (
        <div key={i}>
          <input
            type="radio" name="ans" value={opt}
            checked={answers[currentQuestionIndex] === opt}
            onChange={handleAnswerChange}
          /> <label>{opt}</label>
        </div>
      ))}
      <button onClick={handleNext}>
        {currentQuestionIndex < questions.length - 1 ? 'Next' : 'Finish'}
      </button>
    </div>
  );
}

export default QuizMenuPage;
