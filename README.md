# CS180-Group-Project: MajorMind: an Engineering Major Recommender

Project Description: A web service that allows students and teachers to sign in, and either manage their classrooms of students (for teachers) or to take and assess a quiz that assesses matchings to specific engineering major groups.

Project Motivation: Many engineering students struggle to find the right major. Many decide on one major only to switch or go undeclared in college. Major switches can be costly in money and time, as students take courses they ultimately don’t need for their eventual major. This project is meant to help students avoid that headache by identifying their strengths and interests to find the best major for them.

Goals:
Help high school students determine their best-fit engineering major through a personality-style quiz.
Provide teachers with a classroom dashboard to manage and view student quiz results.

Tools:
Frontend: ReactJS, JavaScript, HTML, CSS
Backend: C++ (cpp-httplib, MD5Crypt), Python 3 (FRQ scripts)
Libraries: Nlohmann JSON (C++), React Router, Axios

Architecture:
Client/Server architecture - allows us to serve many clients
Server: handles account, classroom, quiz logic in C++
Clients: interact via ReactJS frontend (browser-based UI)
Design Patterns:
Object-Oriented Programming (OOP) for modularity
Separates responsibilities
Builder pattern for constructing complex objects  like Accounts and Classrooms
Test-Driven Development
