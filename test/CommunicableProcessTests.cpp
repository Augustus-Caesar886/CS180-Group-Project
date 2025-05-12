#include "../header/CommunicableProcess.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::InSequence;

TEST(CommunicableProcessTests, testProcess) {
    CommunicableProcess p("", "echo");
}