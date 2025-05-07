import React, { useState } from 'react'; // bring in react library and the useState function to manage component states (variables that change)
import { useNavigate } from 'react-router-dom'; // allows changing pages

function LoginPage() { // react component which is a function that returns jsx (html code)
  const [role, setRole] = useState('student');
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [classroomCode, setClassroomCode] = useState('');
  const navigate = useNavigate(); // lets you change page from code

  const handleLogin = () => { // function for when user clicks log in button
    if (!username || !password) {
      alert('Please enter a username and password.');
      return;
    }

    if (role === 'student') {
      if (classroomCode === 'ABC123') {
        navigate('/student', { state: { username } });
      } else {
        alert('Invalid classroom code!');
      }
    } else {
      navigate('/teacher', { state: { username } });
    }
  };

  return (
    <div style={{ padding: '2rem' }}>
      <h2>Login</h2>

      <label>
        Role:
        <select value={role} onChange={e => setRole(e.target.value)}>
          <option value="student">Student</option>
          <option value="teacher">Teacher</option>
        </select>
      </label>

      <br /><br />

      <label>
        Username:
        <input value={username} onChange={e => setUsername(e.target.value)} />
      </label>

      <br /><br />

      <label>
        Password:
        <input type="password" value={password} onChange={e => setPassword(e.target.value)} />
      </label>

      <br /><br />

      {role === 'student' && (
        <>
          <label>
            Classroom Code:
            <input value={classroomCode} onChange={e => setClassroomCode(e.target.value)} />
          </label>
          <br /><br />
        </>
      )}

      <button onClick={handleLogin}>Log In</button>
    </div>
  );
}

export default LoginPage;