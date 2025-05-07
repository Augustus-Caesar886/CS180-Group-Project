// App.js
import React from 'react';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';import LoginPage from './loginPage';
import StudentMenuPage from './studentMenuPage';
import TeacherMenuPage from './teacherMenuPage';
import QuizMenuPage from './quizMenuPage';
import QuizResultPage from './quizResultPage';

function App() {
  return (
    <Router>
      <Routes>
        <Route path="/" element={<LoginPage />} />
        <Route path="/student" element={<StudentMenuPage />} />
        <Route path="/teacher" element={<TeacherMenuPage />} />
        <Route path="/quiz" element={<QuizMenuPage />} />
        <Route path="/result" element={<QuizResultPage />} />
      </Routes>
    </Router>
  );
}

export default App;