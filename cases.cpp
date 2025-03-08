#include "cases.h"

using namespace xx;

int CommandTable::DistributeCommands(const CommandLineData& CData)
{
    std::unordered_map<std::string, bool(*)(const CommandLineData&)> hashMapOfFunction = 
    {
        {"rm", Commands::RemoveFiles},
        {"touch", Commands::CreateFile},
        {"echo", Commands::CreateAndWrite},
        {"mv", Commands::Rename},
        {"cat", Commands::PrintContent},
        {"mkdir", Commands::MakeDirectory},
        {"rmdir", Commands::RemoveDirectory},
        {"ls", Commands::ListFiles},
        {"find", Commands::FindFile},
    };

    if(CData.GetLength() == 0)
    {
        std::cout << "Length is 0" <<std::endl;
        return -1;
    }

    if(CData.GetArgument(0) == nullptr)
    {
        std::cout << "No second argument" << std::endl;
        return -1;
    }

    const std::string CComand = std::string(CData.GetArgument(0));

    if(hashMapOfFunction.find(CComand) == hashMapOfFunction.end())
    {
        return false;
    }

    auto func = hashMapOfFunction.at(CComand);
    return func(CData);
}
