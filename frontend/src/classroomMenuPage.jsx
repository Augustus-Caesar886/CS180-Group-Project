import React, { useState, useEffect } from 'react';

function ClassroomMenuPage({ match }) {
  const classroomCode = match.params.code;
  const [classroom, setClassroom] = useState(null);
  const [sortOption, setSortOption] = useState('alphabetically');

  useEffect(() => {
    const classes = JSON.parse(localStorage.getItem('classrooms')) || [];
    const cls = classes.find(c => c.code === classroomCode);
    setClassroom(cls);
  }, [classroomCode]);

  if (!classroom)
    return (
      <div style={{ padding: '2rem', color: '#b00', fontFamily: 'Arial, sans-serif' }}>
        Loading or classroom not found.
      </div>
    );

  const sortedByName = [...classroom.students].sort((a, b) =>
    a.username.localeCompare(b.username)
  );

  const byMajor = classroom.students.reduce((acc, s) => {
    (acc[s.major] = acc[s.major] || []).push(s);
    return acc;
  }, {});

  return (
    <div style={{ padding: '2rem', fontFamily: 'Arial, sans-serif', color: '#333' }}>
      <h2 style={{ color: '#003366' }}>
        {classroom.name} ({classroom.code})
      </h2>

      <div style={{ marginBottom: '1rem' }}>
        <button
          onClick={() => setSortOption('alphabetically')}
          style={{
            marginRight: '0.5rem',
            padding: '0.5rem 1rem',
            backgroundColor: sortOption === 'alphabetically' ? '#003366' : '#ccc',
            color: sortOption === 'alphabetically' ? '#fff' : '#000',
            border: 'none',
            borderRadius: '4px',
            cursor: 'pointer',
          }}
        >
          Sort A–Z
        </button>

        <button
          onClick={() => setSortOption('byMajor')}
          style={{
            padding: '0.5rem 1rem',
            backgroundColor: sortOption === 'byMajor' ? '#003366' : '#ccc',
            color: sortOption === 'byMajor' ? '#fff' : '#000',
            border: 'none',
            borderRadius: '4px',
            cursor: 'pointer',
          }}
        >
          Group by Major
        </button>
      </div>

      {sortOption === 'alphabetically' ? (
        <ul>
          {sortedByName.map((s) => (
            <li key={s.username} style={{ marginBottom: '0.25rem' }}>
              {s.username} {s.major && <span style={{ color: '#666' }}>({s.major})</span>}
            </li>
          ))}
        </ul>
      ) : (
        Object.entries(byMajor).map(([maj, students]) => (
          <div key={maj} style={{ marginBottom: '1rem' }}>
            <h4 style={{ color: '#003366' }}>{maj || 'Undeclared'}</h4>
            <ul>
              {students.map((s) => (
                <li key={s.username} style={{ marginBottom: '0.25rem' }}>
                  {s.username}
                </li>
              ))}
            </ul>
          </div>
        ))
      )}
    </div>
  );
}

export default ClassroomMenuPage;
