#include "../header/AccountStorage.h"
#include "../header/json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;

AccountStorage::AccountStorage(const std::string& filename) : filename(filename) {}

vector<Account> AccountStorage::loadAccounts() const {
    ifstream inFile(filename);
    if (!inFile.is_open() || inFile.peek() == ifstream::traits_type::eof()) {
        return {};
    }

    json j;
    inFile >> j;

    vector<Account> accounts;
    for (const auto& item : j) {
        Account acc = Account::builder()
            .username(item["username"])
            .passkey(item["passkey"]) // already hashed
            .build();
        accounts.push_back(acc);
    }

    return accounts;
}

void AccountStorage::saveAccounts(const vector<Account>& accounts) const {
    json j;
    for (const auto& acc : accounts) {
        j.push_back({
            {"username", acc.getUsername()},
            {"passkey", acc.getPasskey()}
        });
    }

    ofstream outFile(filename);
    outFile << j.dump(4);
}
