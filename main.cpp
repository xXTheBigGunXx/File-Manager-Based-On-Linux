#include "cases.h"

int main(int argc, char* argv[])
{ 
    CommandLineData Data(argc, argv);
    return xx::CommandTable::DistributeCommands(Data);
}