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

TEST(GetterTests, testGetters) {
    Account test = MockAccount::builder().username("testusername").passkey("testpasskey").build();
    EXPECT_TRUE(test.getPasskey() == "c248e14a2f62fd7d99337da21e59d586");
    EXPECT_FALSE(test.getPasskey() == "testpasskey");
    EXPECT_TRUE(test.getUsername() == "testusername");
    EXPECT_FALSE(test.getUsername() == "testtusername");

    // Hashed passkey: c248e14a2f62fd7d99337da21e59d586
}