import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';

function LoginPage() {
  const [role, setRole] = useState('student');
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [studentCode, setStudentCode] = useState('');
  const [isRegistering, setIsRegistering] = useState(false);
  const navigate = useNavigate();

  const handleRoleChange = (e) => setRole(e.target.value);

  const handleSubmit = () => {
    const users = JSON.parse(localStorage.getItem('users')) || [];

    if (isRegistering) {
      if (!username || !password || (role === 'student' && !studentCode)) {
        alert('Please fill in all required fields.');
        return;
      }

      // 1️⃣ Save user
      users.push({ username, password, role, studentCode });
      localStorage.setItem('users', JSON.stringify(users));

      // 2️⃣ If student, add to classroom
      if (role === 'student') {
        const classrooms = JSON.parse(localStorage.getItem('classrooms')) || [];
        const classroom = classrooms.find(c => c.code === studentCode);
        if (classroom) {
          classroom.students.push({ username, major: null });
          localStorage.setItem('classrooms', JSON.stringify(classrooms));
        } else {
          alert('Warning: classroom code not found.');
        }
      }

      alert(`${role.charAt(0).toUpperCase() + role.slice(1)} registered!`);
      navigate(`/${role}`, { state: { username } });

    } else {
      // Login
      const user = users.find(u =>
        u.username === username &&
        u.password === password &&
        u.role === role
      );
      if (user) {
        navigate(`/${role}`, { state: { username } });
      } else {
        alert('Invalid credentials!');
      }
    }
  };

  return (
    <div style={{ padding: '2rem' }}>
      <h2>{isRegistering ? `Register as ${role}` : 'Login'}</h2>

      <div>
        <label>
          <input
            type="radio" name="role" value="student"
            checked={role === 'student'}
            onChange={handleRoleChange}
          /> Student
        </label>
        <label style={{ marginLeft: '1rem' }}>
          <input
            type="radio" name="role" value="teacher"
            checked={role === 'teacher'}
            onChange={handleRoleChange}
          /> Teacher
        </label>
      </div>

      <div style={{ marginTop: '1rem' }}>
        <div>
          <label>Username:
            <input
              type="text" value={username}
              onChange={e => setUsername(e.target.value)}
            />
          </label>
        </div>
        <div>
          <label>Password:
            <input
              type="password" value={password}
              onChange={e => setPassword(e.target.value)}
            />
          </label>
        </div>
        {role === 'student' && isRegistering && (
          <div>
            <label>Student Code:
              <input
                type="text" value={studentCode}
                onChange={e => setStudentCode(e.target.value)}
              />
            </label>
          </div>
        )}
      </div>

      <div style={{ marginTop: '1rem' }}>
        <button onClick={handleSubmit}>
          {isRegistering ? 'Register' : 'Log In'}
        </button>
        <button
          style={{ marginLeft: '1rem' }}
          onClick={() => setIsRegistering(!isRegistering)}
        >
          {isRegistering ? 'Already have an account?' : 'Need an account?'}
        </button>
      </div>
    </div>
  );
}

export default LoginPage;
