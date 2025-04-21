#ifndef TEACHER_H
#define TEACHER_H

#include "Account.h"
#include "Classroom.h"
#include <list>
using std::list;

//TODO: make more comprehensive when Classroom is implemented
class Teacher : public Account {
    public:
        using collectionType = list<Classroom>;
    private:
        collectionType classroomList;
    public: 
        class TeacherBuilder : public Account::AccountBuilder {
            
        };
        const collectionType& viewClassroomList() const { return classroomList; }
        void createClassroom();

};

#endif