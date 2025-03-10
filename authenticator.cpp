#include "authenticator.h"
#include <iostream>

std::string commandFileLocation = std::string("commands.md");

std::unordered_set<std::string> Authentication::CFilesTypes = {".txt", ".exe", ".md"};

bool Authentication::IsTextFile(const std::string& filesName)
{
    const size_t CIndexOfDot = filesName.rfind('.');
    if(CIndexOfDot == filesName.length())
    {
        return false;
    }
    const std::string filesType = filesName.substr(CIndexOfDot);
    return CFilesTypes.find(filesType) != CFilesTypes.end();
}

constexpr void Print()