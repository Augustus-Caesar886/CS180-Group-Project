#include "../header/Classroom.h"

void Classroom::addStudent(Student& input) {
    students.push_back(input);
}

bool Classroom::removeStudent(Student& input) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (input == *it) {  
            students.erase(it);
            return true;
        }
    }
    return false;
}

vector<Student> Classroom::viewStudentsAlp() {
    vector<Student> sortedStudents = students;
    sort(sortedStudents.begin(), sortedStudents.end());
    return sortedStudents;
}

string Classroom::viewMajor(const Student input) {
    return input.getCurrentMajor(); 
}