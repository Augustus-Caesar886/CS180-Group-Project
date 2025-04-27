#ifndef STUDENT_H
#define STUDENT_H

#include "Account.h"

using std::string;

class Student : public Account {
    private:
        int classroomCode;
        string currentMajor;
    public:
        int getClassroomCode() const { return classroomCode; }
        string getCurrentMajor() const { return currentMajor; }
        class StudentBuilder : public AccountBuilder {
            private:
                int _classroomCode;
                string _currentMajor;
            public:
                StudentBuilder &username(const string&);
                StudentBuilder &passkey(const string&);
                StudentBuilder &classroomCode(int);
                StudentBuilder &currentMajor(const string&);
                Student build() const;
        };
        friend class StudentBuilder;
        static StudentBuilder builder() { return StudentBuilder(); }
//classroom code: int
//currentMajor: string
};

#endif