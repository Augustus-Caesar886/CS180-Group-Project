#include "../header/Teacher.h"

//TODO: make more comprehensive when Classroom is implemented

void Teacher::createClassroom() {
    if(classroomList.size() > 0) return;
    
    Classroom c;
    classroomList.push_back(c);
}