#include "commandImplementation.h"

bool Commands::RemoveFiles(const CommandLineData& CData)
{
    for(size_t i = 1; i < CData.GetLength(); i++)
    {
        std::string filesPath = CData.GetArgument(i);

        if (Authentication::IsTextFile(filesPath) == false)
            continue;

        else if(std::filesystem::remove(filesPath) == false)
            std::cout << "Can't remove a file named: "<< filesPath << '\n'; 
    }
    return true;
}

bool Commands::CreateFile(const CommandLineData& CData)
{
    for(size_t i = 1; i < CData.GetLength(); i++)
    {
        const std::string filesName = CData.GetArgument(i);
        std::ofstream file(filesName);

        if(file.is_open() == false || Authentication::IsTextFile(filesName) == false)
            std::cout << "Can't create a file: " << filesName << '\n'; 
        file.close();
    }
    return true;
}

bool Commands::CreateAndWrite(const CommandLineData& CData)
{
    const std::string filesName = CData.GetArgument(3);
    if(CData.GetLength() != 4 || !Authentication::IsTextFile(filesName))
    {
        return false;  
    }

    std::ofstream file;

    if(std::string(CData.GetArgument(2)).compare(">>") == 0)
        file.open(filesName, std::ios::app);

    else if (std::string(CData.GetArgument(2)).compare(">") == 0)
        file.open(filesName, std::ios::trunc);
    else
    {
        std::cout << "Cannot identifie the file mode: " << CData.GetArgument(2) << '\n'; 
        return false;
    }

    file << CData.GetArgument(1);
    return true;
}

bool Commands::Rename(const CommandLineData& CData)
{
    const std::string firstFile = CData.GetArgument(1);
    const std::string secondFile = CData.GetArgument(2);

    if(CData.GetLength() != 3 || !Authentication::IsTextFile(firstFile) || !Authentication::IsTextFile(secondFile))
        std::cout << "One of a files in not a correct type of format file:" << firstFile << ", " << secondFile << '\n';
        return false;

    std::filesystem::rename(firstFile, secondFile);
    return true;
}

bool Commands::PrintContent(const CommandLineData& CData)
{
    if(CData.GetLength() == 2)
    {
        std::string filesPath = CData.GetArgument(1);
        if(!Authentication::IsTextFile(filesPath))
            return false;

        std::ifstream file(filesPath);

        while(file.is_open() == true && std::getline(file, filesPath))
        {
            std::cout << filesPath << '\n';
        }
        return true;
    }
    else if(CData.GetLength() == 3)
    {
        std::ofstream file;

        if(CData.GetArgument(1).compare(">>") == 0)
        {
            CommandLineData temp(CData);
            temp.ChangeToRead();
            PrintContent(temp);
            file.open(CData.GetArgument(2), std::ios::app);
        }
        else if (std::string(std::string(CData.GetArgument(1))).compare(">") == 0)
        {
            file.open(CData.GetArgument(2), std::ios::trunc);
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
    return std::filesystem::create_directories(CData.GetArgument(1));   
}

bool Commands::RemoveDirectory(const CommandLineData& CData)
{
    if(CData.GetLength() != 2)
        throw std::runtime_error("!!!");
    return std::filesystem::remove(CData.GetArgument(1));
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
    
    std::filesystem::path directPath = CData.GetArgument(1);
    std::string options = CData.GetArgument(2);
    std::string filesName = CData.GetArgument(3);

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
    
    return std::string("");
}
