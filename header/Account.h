#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

using std::string;

class Account {
    protected:
        string username;
        string passkey;
    public:
        class AccountBuilder {
            protected:
                string _username;
                string _passkey;
            public:
                AccountBuilder() : _username(""), _passkey("") {}
                AccountBuilder &username(const string&);
                AccountBuilder &passkey(const string&);
                Account build() const;
        };
        friend class AccountBuilder;
        static AccountBuilder builder() { return AccountBuilder(); }
        bool authenticate(const string& username, const string& passkey) const { return (username == this->username) and (passkey == this->passkey); }
};

#endif