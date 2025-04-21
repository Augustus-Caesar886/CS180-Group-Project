#include "../header/Account.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::InSequence;

#include "../header/Teacher.h"

TEST(TeacherTests, testClassroomManagement) {
    Teacher t = Teacher::builder().username("M").passkey("123").build();
    
    EXPECT_EQ(t.viewClassroom().size(), 0);

    t.createClassroom();

    //TODO: make tests comprehensive when Classroom is implemented
    EXPECT_EQ(t.viewClassroom().size(), 1);

    t.createClassroom();

    EXPECT_EQ(t.viewClassroom().size(), 1);
}