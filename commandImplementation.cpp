#include "commandImplementation.h"

bool Commands::RemoveFiles(const CommandLineData& CData)
{
    for(size_t i = 1; i < CData.GetLength(); i++)
    {
        std::filesystem::path filesPath = std::string(CData.GetArgument(i));
        if(std::filesystem::remove(filesPath) == false)
        {
            throw std::runtime_error("Files path is incorrect");
        }
    }
    return true;
}

bool Commands::CreateFile(const CommandLineData& CData)
{
    for(size_t i = 1; i < CData.GetLength(); i++)
    {
        std::ofstream file(std::string(CData.GetArgument(i)));

        if(file.is_open() == false)
        {
            throw std::runtime_error("Can't create a file!");
        }
        file.close();
    }
    return true;
}

bool Commands::CreateAndWrite(const CommandLineData& CData)
{
    std::cout << "Echo!" <<std::endl;
    if(CData.GetLength() != 4)
    {
        return false;
    }

    std::ofstream file;
    std::cout << CData.GetArgument(2) <<std::endl;

    if(std::string(CData.GetArgument(2)).compare(">>") == 0)
    {
        file.open(std::string(CData.GetArgument(3)), std::ios::app);
    }
    else if (std::string(CData.GetArgument(2)).compare(">") == 0)
    {
        file.open(std::string(CData.GetArgument(3)), std::ios::trunc);
    }
    else
    {
        return false;
    }

    file << CData.GetArgument(1);
    return true;
}

bool Commands::Rename(const CommandLineData& CData)
{
    if(CData.GetLength() != 3)
    {
        return false;
    }
    std::filesystem::rename(std::string(CData.GetArgument(1)), std::string(CData.GetArgument(2)));
    
    return true;
}