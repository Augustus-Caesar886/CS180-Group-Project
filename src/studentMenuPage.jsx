import React from 'react'; // impory react library and components
import { useLocation, useNavigate } from 'react-router-dom'; // allows changing pages

function StudentMenuPage() { // functional component
  const location = useLocation(); // gets data from previous page (current location object)
  const navigate = useNavigate(); // allows navigating to another page
  const username = location.state?.username || 'Student'; // grabs username form location's state object

  const handleTakeQuiz = () => {
    navigate('/quiz', { state: { username } });
  };

  const handleViewResults = () => {
    alert('Feature to view results coming soon!');
  };

  const handleLogout = () => {
    navigate('/'); // sends back to login page
  };

  return (
    <div style={{ padding: '2rem' }}>
      <h2>Welcome, {username} (Student)</h2>
      <button onClick={handleTakeQuiz}>Take Quiz</button>
      <br /><br />
      <button onClick={handleViewResults}>View Results</button>
      <br /><br />
      <button onClick={handleLogout}>Log Out</button>
    </div>
  );
}

export default StudentMenuPage;