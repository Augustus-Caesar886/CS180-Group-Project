#include "../header/CommunicableProcess.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::InSequence;

#include <filesystem>

const bool enableTest = false;

TEST(CommunicableProcessTests, testProcess) {
    if(enableTest) {
        string pythonLocation = "";
        #ifdef __APPLE__ && __MACH__
            pythonLocation = "/Library/Frameworks/Python.framework/Versions/3.12/bin/python3";
        #elif __linux__
            pythonLocation = "/usr/bin/python3";
        #endif
        CommunicableProcess python3(pythonLocation, "python3.12");
        EXPECT_EQ(python3.query("FRQLLM.py I enjoy computing"), "Computer Science");
    }
}
