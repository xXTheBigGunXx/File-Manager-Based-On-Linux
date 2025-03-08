#include "commandImplementation.h"

bool Commands::RemoveFiles(const CommandLineData& CData)
{
    for(size_t i = 1; i < CData.GetLength(); i++)
    {
        std::filesystem::path filesPath = std::string(CData.GetArgument(i));
        if(std::filesystem::remove(filesPath) == false)
            throw std::runtime_error("Files path is incorrect");
    }
    return true;
}

bool Commands::CreateFile(const CommandLineData& CData)
{
    for(size_t i = 1; i < CData.GetLength(); i++)
    {
        std::ofstream file(std::string(CData.GetArgument(i)));

        if(file.is_open() == false)
            throw std::runtime_error("Can't create a file!");
        file.close();
    }
    return true;
}

bool Commands::CreateAndWrite(const CommandLineData& CData)
{
    if(CData.GetLength() != 4)
        return false;  

    std::ofstream file;
    std::cout << CData.GetArgument(2) <<std::endl;

    if(std::string(CData.GetArgument(2)).compare(">>") == 0)
        file.open(std::string(CData.GetArgument(3)), std::ios::app);
    else if (std::string(CData.GetArgument(2)).compare(">") == 0)
        file.open(std::string(CData.GetArgument(3)), std::ios::trunc);
    else
        return false;

    file << CData.GetArgument(1);
    return true;
}

bool Commands::Rename(const CommandLineData& CData)
{
    if(CData.GetLength() != 3)
        return false;
    std::filesystem::rename(std::string(CData.GetArgument(1)), std::string(CData.GetArgument(2)));
    return true;
}

bool Commands::PrintContent(const CommandLineData& CData)
{
    if(CData.GetLength() == 2)
    {
        std::ifstream file(std::string(CData.GetArgument(1)));

        std::string line;
        while(file.is_open() == true && std::getline(file, line))
        {
            std::cout << line << '\n';
        }
        return true;
    }
    else if(CData.GetLength() == 3)
    {
        std::ofstream file;

        if(std::string(CData.GetArgument(1)).compare(">>") == 0)
        {
            file.open((std::string(CData.GetArgument(2))), std::ios::app);
        }
        else if (std::string(std::string(CData.GetArgument(1))).compare(">") == 0)
        {
            file.open(std::string(CData.GetArgument(2)), std::ios::trunc);
        }
        else
        {
            throw std::runtime_error("Error!");
        }

        std::string line;
        while(std::getline(std::cin, line))
        {
            if(line.find("^D") != std::string::npos)
                return false;
            file << line << '\n';
            std::cout << line << std::endl;
        }
        
        file.close();
        return true;
    }
    else
    {
        throw std::runtime_error("Erro!");
    }
}

bool Commands::MakeDirectory(const CommandLineData& CData)
{
    if(CData.GetLength() != 2)
        throw std::runtime_error("!!!");
    return std::filesystem::create_directories(std::string(CData.GetArgument(1)));   
}

bool Commands::RemoveDirectory(const CommandLineData& CData)
{
    if(CData.GetLength() != 2)
        throw std::runtime_error("!!!");
    return std::filesystem::remove(std::string(CData.GetArgument(1)));
}

bool Commands::ListFiles(const CommandLineData& CData)
{
    const std::filesystem::path filesPath = std::filesystem::current_path();
    for(const auto& i : std::filesystem::directory_iterator(filesPath))
    {
        std::cout << i.path() << '\n';
    }
    return true;
}

bool Commands::FindFile(const CommandLineData& CData)
{
    if(CData.GetLength() != 4)
        throw std::runtime_error("!!!");
    
    std::filesystem::path directPath = std::string(CData.GetArgument(1));
    std::string options = std::string(CData.GetArgument(2));
    std::string filesName = std::string(CData.GetArgument(3));

    if (!std::filesystem::exists(directPath) || !std::filesystem::is_directory(directPath))
        throw std::runtime_error("Invalid directory!");

    if(directPath.compare(".") == 0 || options[0] == '-')
    {
        directPath = std::filesystem::current_path();
    }

    const std::string name = LoopDirectory(directPath, filesName);
    if(name.empty() == 0)
    {
        std::cout << name << '\n';
        return true;
    }

    std::cout << "File is not found." << '\n';
    return true;
}

std::string Commands::LoopDirectory(std::filesystem::path& directoriesPath, const std::string& fileName)
{
    for (const auto& i : std::filesystem::directory_iterator(directoriesPath))
    {
        std::filesystem::path filesOrDirecPath = i.path();

        if (std::filesystem::is_directory(filesOrDirecPath))
        {
            std::string result = LoopDirectory(filesOrDirecPath, fileName);
            if (!result.empty())
                return result;
        }
        else if (std::filesystem::is_regular_file(filesOrDirecPath))
        {
            if (filesOrDirecPath.filename().string() == fileName)
                return filesOrDirecPath.string();
        }
    }
    
    return "";
}
