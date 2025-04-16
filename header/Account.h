#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

using std::string;

class Account {
    private:
        string username;
        string passkey;
    public:
        bool authenticate(const string& username, const string& passkey) { return (username == this->username) and (passkey == this->passkey); }
};

#endif