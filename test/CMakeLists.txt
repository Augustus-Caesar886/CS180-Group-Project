CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
ADD_SUBDIRECTORY(googletest)


ADD_EXECUTABLE(MajorMindTests
    ../src/Account.cpp
    AccountTests.cpp
    ../src/Teacher.cpp
    TeacherTests.cpp
    ../src/Student.cpp
    StudentTests.cpp
    ../src/Quiz.cpp
    QuizTests.cpp
    ../src/json.cpp
    JSONQuizReaderTests.cpp
    ../src/JSONQuizReader.cpp
    ../src/md5.cpp
    ../src/AccountStorage.cpp
)

target_link_libraries(MajorMindTests gmock gtest gtest_main)