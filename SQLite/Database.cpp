#include "../header/Database.h"
#include <iostream>

Database::Database(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
}

Database::~Database() {
    if (db) sqlite3_close(db);
}

void Database::createTables() {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Accounts (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            passkey TEXT NOT NULL,
            type TEXT CHECK(type IN ('Student', 'Teacher')) NOT NULL
        );

        CREATE TABLE IF NOT EXISTS Students (
            account_id INTEGER PRIMARY KEY,
            classroomCode INTEGER,
            currentMajor TEXT,
            FOREIGN KEY(account_id) REFERENCES Accounts(id)
        );

        CREATE TABLE IF NOT EXISTS Teachers (
            account_id INTEGER PRIMARY KEY,
            FOREIGN KEY(account_id) REFERENCES Accounts(id)
        );
    )";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void Database::insertStudent(const Student& s) {
    sqlite3_stmt* stmt;
    const char* insertAccountSQL = "INSERT INTO Accounts (username, passkey, type) VALUES (?, ?, 'Student');";

    if (sqlite3_prepare_v2(db, insertAccountSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, s.getUsername().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, s.getPasskey().c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Failed to insert into Accounts\n";
        }
        sqlite3_finalize(stmt);
    }

    int accountId = (int) sqlite3_last_insert_rowid(db);

    const char* insertStudentSQL = "INSERT INTO Students (account_id, classroomCode, currentMajor) VALUES (?, ?, ?);";
    if (sqlite3_prepare_v2(db, insertStudentSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, accountId);
        sqlite3_bind_int(stmt, 2, s.getClassroomCode());
        sqlite3_bind_text(stmt, 3, s.getCurrentMajor().c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Failed to insert into Students\n";
        }
        sqlite3_finalize(stmt);
    }
}

void Database::insertTeacher(const Teacher& t) {
    sqlite3_stmt* stmt;
    const char* insertAccountSQL = "INSERT INTO Accounts (username, passkey, type) VALUES (?, ?, 'Teacher');";

    if (sqlite3_prepare_v2(db, insertAccountSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, t.getUsername().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, t.getPasskey().c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Failed to insert into Accounts\n";
        }
        sqlite3_finalize(stmt);
    }

    // account_id is assigned but Teachers table is currently minimal
    int accountId = (int) sqlite3_last_insert_rowid(db);
    const char* insertTeacherSQL = "INSERT INTO Teachers (account_id) VALUES (?);";
    if (sqlite3_prepare_v2(db, insertTeacherSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, accountId);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Failed to insert into Teachers\n";
        }
        sqlite3_finalize(stmt);
    }
}

Student Database::loadStudentByUsername(const std::string& username) {
    Student s;
    sqlite3_stmt* stmt;
    const char* query = R"(
        SELECT a.passkey, s.classroomCode, s.currentMajor FROM Accounts a
        JOIN Students s ON a.id = s.account_id
        WHERE a.username = ?;
    )";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string passkey = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            int classroomCode = sqlite3_column_int(stmt, 1);
            std::string major = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

            s = Student::builder()
                .username(username)
                .passkey(passkey)
                .classroomCode(classroomCode)
                .currentMajor(major)
                .build();
        }
        sqlite3_finalize(stmt);
    }
    return s;
}

Teacher Database::loadTeacherByUsername(const std::string& username) {
    Teacher t;
    sqlite3_stmt* stmt;
    const char* query = R"(
        SELECT a.passkey FROM Accounts a
        JOIN Teachers t ON a.id = t.account_id
        WHERE a.username = ?;
    )";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string passkey = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            t = Teacher::builder()
                .username(username)
                .passkey(passkey)
                .build();
        }
        sqlite3_finalize(stmt);
    }
    return t;
}
