#ifndef TEACHER_ACCOUNT_STORAGE_H
#define TEACHER_ACCOUNT_STORAGE_H

#include "Teacher.h"
#include <vector>
#include <string>

class TeacherAccountStorage {
private:
    std::string filename;

public:
    TeacherAccountStorage(const std::string& filename);
    std::vector<Teacher> loadTeachers() const;
    void saveTeachers(const std::vector<Teacher>& teachers) const;
};

#endif
