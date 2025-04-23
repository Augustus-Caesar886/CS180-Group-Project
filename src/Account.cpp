#include "../header/Account.h"

Account::AccountBuilder &Account::AccountBuilder::username(const string& username) {
    this->_username = username;
    return *this;
}

Account::AccountBuilder &Account::AccountBuilder::passkey(const string& passkey) {
    this->_passkey = passkey;
    return *this;
}

Account Account::AccountBuilder::build() const {
    Account acc;
    acc.username = _username;
    acc.passkey = _passkey;
    return acc;
}