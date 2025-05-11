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

  if (!classroom) return <div>Loading or classroom not found.</div>;

  const sortedByName = [...classroom.students].sort((a,b) =>
    a.username.localeCompare(b.username)
  );
  const byMajor = classroom.students.reduce((acc,s) => {
    (acc[s.major] = acc[s.major]||[]).push(s);
    return acc;
  }, {});

  return (
    <div style={{ padding: '2rem' }}>
      <h2>{classroom.name} ({classroom.code})</h2>
      <button onClick={()=>setSortOption('alphabetically')}>Sort A–Z</button>
      <button onClick={()=>setSortOption('byMajor')}>Group by Major</button>

      {sortOption === 'alphabetically' ? (
        <ul>
          {sortedByName.map((s,i) => (
            <li key={i}>{s.username} {s.major && `(${s.major})`}</li>
          ))}
        </ul>
      ) : (
        Object.entries(byMajor).map(([maj, students]) => (
          <div key={maj}>
            <h4>{maj || 'Undeclared'}</h4>
            <ul>
              {students.map((s,i) => (
                <li key={i}>{s.username}</li>
              ))}
            </ul>
          </div>
        ))
      )}
    </div>
  );
}

export default ClassroomMenuPage;
