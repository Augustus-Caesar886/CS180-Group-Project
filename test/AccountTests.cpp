#include "../header/Account.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::InSequence;

class MockAccount : public Account {

};

TEST(AccountTests, testAccount) {
    Account user = MockAccount::builder().username("W").passkey("123").build();
    EXPECT_TRUE(user.authenticate("W", "123"));
    EXPECT_FALSE(user.authenticate("V", "123"));
    EXPECT_FALSE(user.authenticate("W", "456"));
    EXPECT_FALSE(user.authenticate("WW", "123"));
    EXPECT_FALSE(user.authenticate("W", "1234"));
}