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
        <div style={{ padding: '2rem' }}>
            <h2>Teacher Menu</h2>
            <h3>Create Classroom</h3>
            <input
                type="text"
                placeholder="Classroom Code"
                value={classroomCode}
                onChange={(e) => setClassroomCode(e.target.value)}
            />
            <br />
            <input
                type="text"
                placeholder="Classroom Name"
                value={classroomName}
                onChange={(e) => setClassroomName(e.target.value)}
            />
            <br />
            <button onClick={handleCreateClassroom}>Create Classroom</button>
            <br /><br />
            <h3>Your Classrooms</h3>
            {classrooms.length === 0 ? (
                <p>No classrooms yet.</p>
            ) : (
                classrooms.map((classroom, index) => (
                    <div key={index}>
                        <span>{classroom.name} ({classroom.code})</span>
                        <button onClick={() => handleViewClassroom(classroom.code)}>View Classroom</button>
                    </div>
                ))
            )}
        </div>
    );
}

export default TeacherMenuPage;
