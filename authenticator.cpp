#include "authenticator.h"
#include <iostream>

const std::string Authentication::commandFileLocation = std::string("commands.md");

std::unordered_set<std::string> Authentication::CFilesTypes = {".txt", ".exe", ".md"};

bool Authentication::IsTextFile(const std::string& filesName)
{
    const size_t CIndexOfDot = filesName.rfind('.');
    if(CIndexOfDot == filesName.length() || CIndexOfDot == std::string::npos)
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

bool Authentication::CommandLineCheck(const size_t size, const size_t commandLineSize)
{
    if(size != commandLineSize)
    {
        std::cout << "Not enought arguments for this command.\n";
        return false;
    }
    return true;
}