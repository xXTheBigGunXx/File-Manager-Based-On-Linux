#include "cases.h"

using namespace xx;

int CommandTable::DistributeCommands(const CommandLineData& CData)
{
    if(CData.GetLength() == 0)
    {
        std::cout << "Length is 0" <<std::endl;
        return -1;
    }

    const char* temp = CData.GetArgument(0);

    if(temp == nullptr)
    {
        std::cout << "No second argument" << std::endl;
        return -1;
    }

    const std::string CComand = std::string(CData.GetArgument(0));

    if(CComand == "rm")
    {
        Commands::RemoveFiles(CData);
    }
    else if (true)
    {

    }
    return -1;
}
