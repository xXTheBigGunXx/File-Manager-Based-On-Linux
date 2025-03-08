#include "cases.h"
#include "data.h"

int main(int argc, char* argv[])
{ 
    CommandLineData Data(argc, argv);

    /*std::cout << "Arguments count: " << argc << std::endl;
    for (int i = 0; i < Data.GetLength(); i++)
    {
        std::cout << "Arg " << i << ": " << Data.GetArgument(i) << std::endl;
    }*/

    return xx::CommandTable::DistributeCommands(Data);
}