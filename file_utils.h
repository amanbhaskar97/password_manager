#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <map>

namespace FileUtils {
    const std::string FILENAME = "passwords.enc";
    
    void savePasswords(const std::map<std::pair<std::string, std::string>, std::string>& passwords);
    void loadPasswords(std::map<std::pair<std::string, std::string>, std::string>& passwords);
}

#endif // FILE_UTILS_H

