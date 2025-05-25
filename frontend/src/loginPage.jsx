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

  const handleSubmit = async () => {
    if (isRegistering) {
      if (!username || !password || (role === 'student' && !studentCode)) {
        alert('Please fill in all required fields.');
        return;
      }
      //registering new account
      try{
        const response = await fetch('http://localhost:8080/register',{
          method: 'POST',
          headers:{
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({username, password, role, classroomCode: Number(studentCode)}),
        });

        const data = await response.json();

        if(response.ok && data.status === 'success'){
          alert(`${role.charAt(0).toUpperCase() + role.slice(1)} registered successfully!`);
          navigate(`/${role}`, {state: {username}});
        }else{
          alert(data.message || 'Registration failed');
        }
      }catch(error){
        console.error("Registration error:", error);
        alert("Could not connect to server");
      }
    //Login 
    }else {
        try {
          const response = await fetch('http://localhost:8080/login', {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
          },
          body: JSON.stringify({ username, password, role }),
        });

        const data = await response.json();

        if (response.ok && data.status === 'success') {
          navigate(`/${role}`, { state: { username } });
        } else {
          alert(data.message || 'Login failed');
        }
      } catch (error) {
          console.error('Login error:', error);
          alert('Could not connect to server');
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


//just major stored in json