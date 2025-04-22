#ifndef TEACHER_H
#define TEACHER_H

#include "Account.h"
#include "Classroom.h"
#include <list>

using std::string;
using std::list;

//TODO: make more comprehensive when Classroom is implemented
class Teacher : public Account {
    public:
        using collectionType = list<Classroom>;
    private:
        collectionType classroomList;
    public: 
        class TeacherBuilder : public Account::AccountBuilder {
            public:
                TeacherBuilder &username(const string&);
                TeacherBuilder &passkey(const string&);
                Teacher build() const;
        };
        friend class TeacherBuilder;
        static TeacherBuilder builder() { return TeacherBuilder(); }
        const collectionType& viewClassroomList() const { return classroomList; }
        void createClassroom();

};

#endif