#include "cases.h"
#include "authenticator.h"

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
        {"man", Commands::PrintCommands},
    };

    if(CData.GetLength() == 0)
    {
        std::cout << "No command line arguments are passed into a file.\n";
        return -1;
    }

    const std::string CComand = CData.GetArgument(0);
    std::cout <<CComand << '|' << std::endl;

    if(CComand.compare("") == 0 || hashMapOfFunction.find(CComand) == hashMapOfFunction.end())
    {
        std::cout << "Cannot identifie the command.\n";
        return -1;
    }

    bool (*func)(const CommandLineData&) = hashMapOfFunction.at(CComand);
    return func(CData);
    return 0;
}
