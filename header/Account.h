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
        bool authenticate(const string& username1, const string& passkey1) const { return (username1 == this->username) && (computeHash(passkey1) == this->passkey); }
        string computeHash(const string& passkey) const;          // Hashes passwords when creating an account

        // TESTING ACCOUNT STORAGE: Getters

        string getUsername() const { return this->username; }
        string getPasskey() const { return this->passkey; }
};

#endif