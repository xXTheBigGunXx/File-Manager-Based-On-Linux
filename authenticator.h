#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H


#include "data.h"
#include "commandImplementation.h"
#include <string>
#include <cstddef>
#include <unordered_set>
#include <string>
#include <string_view>

class Authentication
{
private:
    static std::string_view commandFileLocation;
    static std::unordered_set<std::string> CFilesTypes;
public:
    static bool IsTextFile(const std::string& filesName);
    static bool PrintCommands(const CommandLineData& CData);
    static bool CommandLineCheck(const size_t size, const size_t commandLineSize);
};

#endif