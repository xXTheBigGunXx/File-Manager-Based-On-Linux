#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <string>
#include <cstddef>
#include <unordered_set>
#include <string>

class Authentication
{
private:
    constexpr std::string commandFileLocation;
    static std::unordered_set<std::string> CFilesTypes;
public:
    static bool IsTextFile(const std::string& filesName);
};

#endif