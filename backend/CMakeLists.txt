cmake_minimum_required(VERSION 3.0)

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
    src/Quiz.cpp
    src/json.cpp
    src/JSONQuizReader.cpp
    src/md5.cpp
    src/StudentAccountStorage.cpp
    src/TeacherAccountStorage.cpp
    src/Classroom.cpp
)

#nlohmann/json (header-only library)
include(FetchContent)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.2
)


FetchContent_MakeAvailable(json)

# Include cpp-httplib (header-only)
FetchContent_Declare(
  httplib
  GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(httplib)

# Link nlohmann_json and httplib
target_include_directories(MajorMind PRIVATE ${json_SOURCE_DIR}/single_include)
target_include_directories(MajorMind PRIVATE ${httplib_SOURCE_DIR})

target_link_libraries(MajorMind PRIVATE nlohmann_json::nlohmann_json)