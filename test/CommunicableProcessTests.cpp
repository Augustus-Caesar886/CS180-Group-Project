#include "../header/CommunicableProcess.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::InSequence;

#include <filesystem>

const bool disableTest = true;

TEST(CommunicableProcessTests, testProcess) {
    if(not disableTest) {
        CommunicableProcess python3("/usr/bin/python3", "python3.12");
        EXPECT_EQ(python3.query("FRQLLM.py I enjoy computing"), "Computer Science");
    }
}
