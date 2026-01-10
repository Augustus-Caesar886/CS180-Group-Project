#ifndef DATABASE_H
#define DATABASE_H

extern "C" {
    #include "sqlite3.h"
}

#include <string>
#include "Student.h"
#include "Teacher.h"

class Database {
private:
    sqlite3* db;
public:
    Database(const std::string& dbPath);
    ~Database();

    void createTables();

    void insertStudent(const Student& s);
    void insertTeacher(const Teacher& t);

    Student loadStudentByUsername(const std::string& username);
    Teacher loadTeacherByUsername(const std::string& username);
};

#endif
