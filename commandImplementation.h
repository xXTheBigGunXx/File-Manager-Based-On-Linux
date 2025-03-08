#ifndef COMMANDIMPLEMENTATION_H
#define COMMANDIMPLEMENTATION_H

#include "data.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

class Commands{
    private:
    static std::string LoopDirectory(std::filesystem::path directoriesPath, std::string fileName);
    public:
    static bool RemoveFiles(const CommandLineData CData);
    static bool CreateFile(const CommandLineData CData);
    static bool CreateAndWrite(const CommandLineData CData);
    static bool Rename(const CommandLineData CData);
    static bool PrintContent(const CommandLineData CData);
    static bool MakeDirectory(const CommandLineData CData);
    static bool RemoveDirectory(const CommandLineData CData);
    static bool ListFiles(const CommandLineData CData);
    static bool FindFile(const CommandLineData CData);
};

#endif