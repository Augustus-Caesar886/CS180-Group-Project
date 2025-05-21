#include "../header/StudentAccountStorage.h"
#include "../header/json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;

StudentAccountStorage::StudentAccountStorage(const std::string& filename) : filename(filename) {}

vector<Student> StudentAccountStorage::loadStudents() const {
    ifstream inFile(filename);
    if (!inFile.is_open() || inFile.peek() == ifstream::traits_type::eof()) {
        return {};
    }

    json j;
    inFile >> j;

    vector<Student> students;
    for (const auto& item : j) {
        students.push_back(Student::builder()
            .username(item["username"])
            .passkey(item["passkey"])
            .classroomCode(item["classroomCode"])
            .currentMajor(item["currentMajor"])
            .build());
    }

    return students;
}

void StudentAccountStorage::saveStudents(const vector<Student>& newStudents) const {
    // Step 1: Load existing students
    vector<Student> existing = loadStudents();

    // Step 2: Merge (replace students with same username)
    unordered_map<string, Student> merged;
    for (const auto& s : existing) {
        merged[s.getUsername()] = s;
    }
    for (const auto& s : newStudents) {
        merged[s.getUsername()] = s;  // Overwrite or insert new
    }

    // Step 3: Serialize
    json j;
    for (const auto& [_, s] : merged) {
        j.push_back({
            {"username", s.getUsername()},
            {"passkey", s.getPasskey()},
            {"classroomCode", s.getClassroomCode()},
            {"currentMajor", s.getCurrentMajor()}
        });
    }

    ofstream outFile(filename);
    outFile << j.dump(4);
}

