#include "../header/Account.h"
#include "../header/md5.h"

string Account::computeHash(const string& passkey) const {
    return md5(passkey);
}

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
    acc.passkey = acc.computeHash(_passkey); // Hash the passkey and set that as the password
    return acc;
}