#include "authenticator.h"
#include <iostream>

const std::string Authentication::commandFileLocation = std::string("commands.md");

std::unordered_set<std::string> Authentication::CFilesTypes = {".txt", ".exe", ".md", ".png"};

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

bool Authentication::PrintCommands(const CommandLineData& CData)
{
    CommandLineData temp(CData);
    temp.AddElement(Authentication::commandFileLocation);
    return Commands::PrintContent(temp); 
}