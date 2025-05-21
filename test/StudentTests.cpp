#include "../header/Account.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::InSequence;

#include "../header/Student.h"

TEST(StudentTests, testStudent) {
    Student w = Student::builder().username("w").passkey("123").classroomCode(456).currentMajor("CSBA").build();

    EXPECT_TRUE(w.authenticate("w", "123"));
    EXPECT_FALSE(w.authenticate("w", "122"));
    EXPECT_FALSE(w.authenticate("p", "123"));
    
    EXPECT_EQ(w.getClassroomCode(), 456);
    EXPECT_EQ(w.getCurrentMajor(), "CSBA");
}