#include "cases.h"
#include <string>
#include <filesystem>
#include <iostream>


int CommandTable::DistributeCommands(const CommandLineData& data)
{
    for(size_t i = 0; i < data.GetLength(); i++)
    {
        std::cout << '|' << data.GetArgument(i) << '|' << std::endl;
    }
    return 1;
}

    /*if(data.GetLength() == 0)
    {
        return -1;
    }

    bool flag = true;
    const char* temp = data.GetArgument(1);

    if(temp == nullptr)
    {
        std::cout << "Nera" << std::endl;
        return -1;
    }

    std::filesystem::path filePath = std::string(temp);
    const std::string CComand = std::string(data.GetArgument(0));

    std::cout << '|' << temp << '|' <<std::endl;
    std::cout << '|' << CComand << '|' << std::endl;

    if(CComand == "rm")
    {
        if(std::filesystem::remove(filePath))
        {
            std::cout << "File is deleted: " << filePath << '\n';
        }
        else{
            std::cerr << "GG\n";
        }
    } 
    return -1;
}*/
