#include "../header/TeacherAccountStorage.h"
#include "../header/json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;

TeacherAccountStorage::TeacherAccountStorage(const std::string& filename) : filename(filename) {}

vector<Teacher> TeacherAccountStorage::loadTeachers() const {
    ifstream inFile(filename);
    if (!inFile.is_open() || inFile.peek() == ifstream::traits_type::eof()) {
        return {};
    }

    json j;
    inFile >> j;

    vector<Teacher> teachers;
    for (const auto& item : j) {
        teachers.push_back(Teacher::builder()
            .username(item["username"])
            .passkey(item["passkey"])
            .build());
    }

    return teachers;
}

void TeacherAccountStorage::saveTeachers(const vector<Teacher>& newTeachers) const {
    vector<Teacher> existing = loadTeachers();

    unordered_map<string, Teacher> merged;
    for (const auto& t : existing) {
        merged[t.getUsername()] = t;
    }
    for (const auto& t : newTeachers) {
        merged[t.getUsername()] = t;
    }

    json j;
    for (const auto& [_, t] : merged) {
        j.push_back({
            {"username", t.getUsername()},
            {"passkey", t.getPasskey()}
        });
    }

    ofstream outFile(filename);
    outFile << j.dump(4);
}

