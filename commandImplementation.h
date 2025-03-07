#ifndef COMMANDIMPLEMENTATION_H
#define COMMANDIMPLEMENTATION_H

#include "data.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

class Commands{
    public:
    static bool RemoveFiles(const CommandLineData& CData);
    static bool CreateFile(const CommandLineData& CData);
    static bool CreateAndWrite(const CommandLineData& CData);
    static bool Rename(const CommandLineData& CData);
};

#endif