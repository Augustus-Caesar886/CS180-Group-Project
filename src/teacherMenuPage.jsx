import React from 'react'; // import react library and components
import { useLocation, useNavigate } from 'react-router-dom'; // allows changing pages

function TeacherMenuPage() {
    const location = useLocation(); // gets data from login page
    const navigate = useNavigate();
    const username = location.state?.username || 'Teacher';

    const handleCreateClassroom = () => {
        alert('Feature to create classroom coming soon!');
    };

    const handleViewClassroomList = () => {
        alert('Feature to view classroom list coming soon!');
    };

    const handleLogout = () => {
        navigate('/'); // sends back to login page
    };

    return (
        <div style={{ padding: '2rem' }}>
            <h2>Welcome, {username} (Teacher)</h2>
            <button onClick = {handleCreateClassroom}>Create Classroom</button>
            <br /><br />
            <button onClick = {handleViewClassroomList}>View Classroom List</button>
            <br /><br />
            <button onClick = {handleLogout}>Log Out</button>
        </div>
    );
}

export default TeacherMenuPage;

