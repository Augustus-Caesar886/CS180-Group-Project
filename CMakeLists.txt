CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(MajorMind)

set(CMAKE_CXX_STANDARD 17)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

ADD_EXECUTABLE(MajorMind
    src/main.cpp
    src/Account.cpp
    src/Teacher.cpp
    src/Student.cpp
    src/md5.cpp
    src/CommunicableProcess.cpp
    src/Quiz.cpp
    src/json.cpp
    src/JSONQuizReader.cpp
    src/StudentAccountStorage.cpp
    src/TeacherAccountStorage.cpp
    src/Classroom.cpp
)