#include "cases.h"
#include "data.h"

int main(int argc, char* argv[])
{
    CommandLineData Data(argc, argv);

    std::cout << Data.len << std::endl;

    /*for(size_t i = 0; i < Data.len; i++)
    {
        std::cout << Data.data[i] << std::endl;
    }*/

    xx::CommandTable::DistributeCommands(Data);
}