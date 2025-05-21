#include "../header/CommunicableProcess.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::InSequence;

#include <filesystem>

TEST(CommunicableProcessTests, testProcess) {
    CommunicableProcess python3("/Library/Frameworks/Python.framework/Versions/3.12/bin/python3", "python3");
    EXPECT_EQ(python3.query("FRQLLM.py I enjoy computing"), "Computer Science");
}