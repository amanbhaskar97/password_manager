#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <string>
#include <map>

class PasswordManager {
public:
    PasswordManager();
    void loadPasswords();
    void savePasswords();
    bool checkMasterPassword();
    void addPassword();
    void retrievePassword();
    void showAllPasswords();
    void modifyPassword();
    void deletePassword();
    std::string suggestPassword();

private:
    std::map<std::pair<std::string, std::string>, std::string> passwords;
    void setupMasterPassword();
};

#endif // PASSWORD_MANAGER_H

