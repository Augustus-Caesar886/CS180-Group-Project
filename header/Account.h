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
        string computeHash(const string& passkey) const;            // Hashes passwords when creating an account
        bool authenticate(const string& username, const string& passkey) const { return (username == this->username) && (computeHash(passkey) == computeHash(this->passkey)); }
};

#endif