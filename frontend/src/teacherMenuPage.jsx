import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';

function TeacherMenuPage() {
  const navigate = useNavigate();
  const [classroomCode, setClassroomCode] = useState('');
  const [classroomName, setClassroomName] = useState('');
  const [classrooms, setClassrooms] = useState(() => {
    const savedClassrooms = localStorage.getItem('classrooms');
    return savedClassrooms ? JSON.parse(savedClassrooms) : [];
  });

  const handleCreateClassroom = () => {
    if (classroomCode && classroomName) {
      const newClassroom = { code: classroomCode, name: classroomName, students: [] };
      const updatedClassrooms = [...classrooms, newClassroom];
      localStorage.setItem('classrooms', JSON.stringify(updatedClassrooms));
      setClassrooms(updatedClassrooms);
      alert('Classroom created successfully!');
    } else {
      alert('Please enter both classroom code and name!');
    }
  };

  const handleViewClassroom = (classroomCode) => {
    navigate(`/classroom/${classroomCode}`, { state: { classrooms } });
  };

  return (
    <div style={{
      padding: '2rem',
      backgroundColor: '#eef3ff',
      borderRadius: '12px',
      maxWidth: '650px',
      margin: '2rem auto',
      fontFamily: 'Arial, sans-serif',
      boxShadow: '0 4px 12px rgba(0,0,0,0.1)',
      color: '#333'
    }}>
      <h2 style={{ color: '#2b3a67', fontSize: '1.8rem', marginBottom: '1rem' }}>Teacher Menu</h2>

      <h3 style={{ color: '#2b3a67', fontSize: '1.3rem' }}>Create Classroom</h3>

      <input
        type="text"
        placeholder="Classroom Code"
        value={classroomCode}
        onChange={(e) => setClassroomCode(e.target.value)}
        style={{
          padding: '0.5rem',
          marginBottom: '0.5rem',
          width: '100%',
          border: '1px solid #ccc',
          borderRadius: '6px',
          fontSize: '1rem'
        }}
      />
      <br />
      <input
        type="text"
        placeholder="Classroom Name"
        value={classroomName}
        onChange={(e) => setClassroomName(e.target.value)}
        style={{
          padding: '0.5rem',
          marginBottom: '1rem',
          width: '100%',
          border: '1px solid #ccc',
          borderRadius: '6px',
          fontSize: '1rem'
        }}
      />
      <br />
      <button
        onClick={handleCreateClassroom}
        style={{
          padding: '0.6rem 1.2rem',
          fontSize: '1rem',
          backgroundColor: '#4e63ea',
          color: 'white',
          border: 'none',
          borderRadius: '8px',
          cursor: 'pointer',
          transition: 'background-color 0.2s ease',
          marginBottom: '2rem'
        }}
        onMouseOver={e => e.target.style.backgroundColor = '#3a4dc4'}
        onMouseOut={e => e.target.style.backgroundColor = '#4e63ea'}
      >
        Create Classroom
      </button>

      <h3 style={{ color: '#2b3a67', fontSize: '1.3rem' }}>Your Classrooms</h3>

      {classrooms.length === 0 ? (
        <p style={{ color: '#666' }}>No classrooms yet.</p>
      ) : (
        classrooms.map((classroom, index) => (
          <div key={index} style={{
            display: 'flex',
            justifyContent: 'space-between',
            alignItems: 'center',
            padding: '0.75rem',
            marginBottom: '0.5rem',
            backgroundColor: '#fff',
            borderRadius: '8px',
            boxShadow: '0 2px 4px rgba(0,0,0,0.05)'
          }}>
            <span style={{ fontSize: '1rem' }}>{classroom.name} ({classroom.code})</span>
            <button
              onClick={() => handleViewClassroom(classroom.code)}
              style={{
                padding: '0.5rem 1rem',
                fontSize: '0.95rem',
                backgroundColor: '#00b894',
                color: 'white',
                border: 'none',
                borderRadius: '6px',
                cursor: 'pointer',
                transition: 'background-color 0.2s ease'
              }}
              onMouseOver={e => e.target.style.backgroundColor = '#019875'}
              onMouseOut={e => e.target.style.backgroundColor = '#00b894'}
            >
              View Classroom
            </button>
          </div>
        ))
      )}
    </div>
  );
}

export default TeacherMenuPage;
