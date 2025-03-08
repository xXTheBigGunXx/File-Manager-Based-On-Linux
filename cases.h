#ifndef CASES_H
#define CASES_H

#include "data.h"
#include "commandImplementation.h"
#include <string>
#include <iostream>
#include <exception>
#include <unordered_map>

namespace xx
{

    class CommandTable{
    private:
    public:
        CommandTable();
        static int DistributeCommands(const CommandLineData& CData);
    };
}

#endif