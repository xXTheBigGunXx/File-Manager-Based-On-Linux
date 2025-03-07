#ifndef COMMANDIMPLEMENTATION_H
#define COMMANDIMPLEMENTATION_H

#include "data.h"
#include <filesystem>

class Commands{
    public:
    static bool RemoveFiles(const CommandLineData& CData);
};

#endif