#ifndef STUDENT_ACOUNT_STORAGE_H
#define STUDENT_ACCOUNT_STORAGE_H

#include "Student.h"
#include <vector>
#include <string>

class StudentAccountStorage {
private:
    std::string filename;

public:
    StudentAccountStorage(const std::string& filename);
    std::vector<Student> loadStudents() const;
    void saveStudents(const std::vector<Student>& students) const;
};

#endif
