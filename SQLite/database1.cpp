#include <iostream>
#include "../header/Database.h"
#include "../header/Student.h"
#include "../header/Teacher.h"

int main() {
    // Connect and set up tables
    Database db("accounts.db");
    db.createTables();

    // Build a Student and add to DB
    // Student s = Student::builder()
    //     .username("alice123")
    //     .passkey("secure123")
    //     .classroomCode(101)
    //     .currentMajor("Chemical Engineering")
    //     .build();

    // db.insertStudent(s);
    // std::cout << "Student inserted.\n";

    // Load student back and print info
    Student loaded = db.loadStudentByUsername("alice123");
    std::cout << "Loaded student:\n";
    std::cout << "Username: " << loaded.getUsername() << "\n";
    std::cout << "Major: " << loaded.getCurrentMajor() << "\n";

    return 0;
}
