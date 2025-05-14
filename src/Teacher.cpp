#include "../header/Teacher.h"

using std::string;

//TODO: make more comprehensive when Classroom is implemented

Teacher Teacher::TeacherBuilder::build() const {
    Teacher t;
    t.username = _username;
    if (_passkey.length() <= 15) {
        t.passkey = t.computeHash(_passkey);
    } else {
        t.passkey = _passkey;
    }
    return t;
}

Teacher::TeacherBuilder &Teacher::TeacherBuilder::username(const string& username) {
    this->_username = username;
    return *this;
}

Teacher::TeacherBuilder &Teacher::TeacherBuilder::passkey(const string& passkey) {
    this->_passkey = passkey;
    return *this;
}

void Teacher::createClassroom() {
    if(classroomList.size() > 0) return;
    
    Classroom c;
    classroomList.push_back(c);
}