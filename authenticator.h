#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H


#include "data.h"
#include "commandImplementation.h"
#include <string>
#include <cstddef>
#include <unordered_set>
#include <string>

class Authentication
{
private:
    static const std::string commandFileLocation;
    static std::unordered_set<std::string> CFilesTypes;
public:
    static bool IsTextFile(const std::string& filesName);
    static bool PrintCommands(const CommandLineData& CData);
};

#endif