#include "../header/CommunicableProcess.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::InSequence;

TEST(CommunicableProcessTests, testProcess) {
    CommunicableProcess p("/bin/sh", "exec sh");
    p.send("echo hi");
    EXPECT_EQ(p.read(), "hi");
}