#include <gtest/gtest.h>
#include "../header/Classroom.h"
#include "../header/Student.h"

class ClassroomTest : public ::testing::Test {
protected:
    Classroom classroom;
    Student s1;
    Student s2;
    Student s3;

    void SetUp() override {
        s1 = Student::builder().username("alice").passkey("pass1").classroomCode(101).currentMajor("CS").build();
        s2 = Student::builder().username("bob").passkey("pass2").classroomCode(101).currentMajor("Math").build();
        s3 = Student::builder().username("charlie").passkey("pass3").classroomCode(101).currentMajor("Physics").build();
    }
};

TEST_F(ClassroomTest, AddStudentIncreasesSize) {
    classroom.addStudent(s1);
    classroom.addStudent(s2);
    EXPECT_EQ(classroom.viewStudentsAlp().size(), 2);
}

TEST_F(ClassroomTest, RemoveStudentSuccessful) {
    classroom.addStudent(s1);
    classroom.addStudent(s2);
    bool removed = classroom.removeStudent(s1);
    EXPECT_TRUE(removed);
    EXPECT_EQ(classroom.viewStudentsAlp().size(), 1);
    EXPECT_EQ(classroom.viewStudentsAlp()[0].getUsername(), "bob");
}

TEST_F(ClassroomTest, RemoveStudentFailsIfNotFound) {
    classroom.addStudent(s1);
    bool removed = classroom.removeStudent(s2); 
    EXPECT_FALSE(removed);
    EXPECT_EQ(classroom.viewStudentsAlp().size(), 1);
}

TEST_F(ClassroomTest, ViewStudentsSortedAlphabetically) {
    classroom.addStudent(s3); 
    classroom.addStudent(s1); 
    classroom.addStudent(s2); 
    std::vector<Student> sorted = classroom.viewStudentsAlp();
    ASSERT_EQ(sorted.size(), 3);
    EXPECT_EQ(sorted[0].getUsername(), "alice");
    EXPECT_EQ(sorted[1].getUsername(), "bob");
    EXPECT_EQ(sorted[2].getUsername(), "charlie");
}

TEST_F(ClassroomTest, ViewMajorReturnsCorrectMajor) {
    EXPECT_EQ(classroom.viewMajor(s1), "CS");
    EXPECT_EQ(classroom.viewMajor(s2), "Math");
    EXPECT_EQ(classroom.viewMajor(s3), "Physics");
}