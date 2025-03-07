#ifndef CASES_H
#define CASES_H

#include "data.h"
#include <string>
#include <filesystem>
#include <iostream>

class CommandTable{
private:
public:
    CommandTable();
    static int DistributeCommands(const CommandLineData& data);
};

//#include "cases.cpp"

#endif