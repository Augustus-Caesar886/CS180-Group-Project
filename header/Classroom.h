#ifndef CLASSROOM_H
#define CLASSROOM_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Student.h"

using std::string;
using std::vector;

class Classroom {
    private:
        int classCode;
        string teacher;
        vector<Student> students;
    public:
        void addStudent(Student& input);
        bool removeStudent(Student& input);
        vector<Student> viewStudentsAlp();
        string viewMajor(const Student input);

};

#endif