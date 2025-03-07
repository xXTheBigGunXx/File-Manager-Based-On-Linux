#include "cases.h"
#include "data.h"

int main(int argc, char* argv[])
{
    CommandLineData Data(argc, argv);

    xx::CommandTable::DistributeCommands(Data);
}