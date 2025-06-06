#include "../header/Student.h"
#include "../header/md5.h"

Student::StudentBuilder &Student::StudentBuilder::username(const string& username) {
    this->_username = username;
    return *this;
}
Student::StudentBuilder &Student::StudentBuilder::passkey(const string& passkey) {
    this->_passkey = passkey;
    return *this;
}
Student::StudentBuilder &Student::StudentBuilder::classroomCode(int code) {
    _classroomCode = code;
    return *this;
}
Student::StudentBuilder &Student::StudentBuilder::currentMajor(const string& major) {
    _currentMajor = major;
    return *this;
}
Student Student::StudentBuilder::build() const {
    Student s;
    s.username = _username;
    if (_passkey.length() <= 15) {
        s.passkey = s.computeHash(_passkey);  // plaintext → hash it
    } else {
        s.passkey = _passkey;  // already hashed
    }
    s.classroomCode = _classroomCode;
    s.currentMajor = _currentMajor;
    return s;
}