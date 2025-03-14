#include "commandImplementation.h"

bool Commands::RemoveFiles(const CommandLineData& CData)
{
    for(size_t i = 1; i < CData.GetLength(); i++)
    {
        const std::string filesPath = CData.GetArgument(i);
        std::error_code er;

        if(std::filesystem::remove(filesPath, er) == false)
            std::cout << "Filesystem library throws error: "<<er.message()<<'\n';
        else if (Authentication::IsTextFile(filesPath) == false)
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
        file.close();

        if(Authentication::IsTextFile(filesName) == false)
        {
            std::cout << "Can't create a file: " << filesName << '\n';
            std::error_code ec;
            if(std::filesystem::remove(filesName, ec) == false)
            {
                std::cout << "Filesystem library throws error: "<<ec.message()<<'\n';
            }  
        }
    }
    return true;
}

bool Commands::CreateAndWrite(const CommandLineData& CData)
{
    const std::string filesName = CData.GetArgument(3);
    
    if(!Authentication::CommandLineCheck(4, CData.GetLength()))
        return false;

    else if (Authentication::IsTextFile(filesName) == false)
    {
        std::cout << "Incorrect file type.\n";
        return false;
    }

    std::ofstream file;

    if(CData.GetArgument(2).compare(">>") == 0)
        file.open(filesName, std::ios::app);

    else if (CData.GetArgument(2).compare(">") == 0)
        file.open(filesName, std::ios::trunc);
    else
    {
        std::cout << "Cannot identifie the file append mode: " << CData.GetArgument(2) << '\n'; 
        return false;
    }

    file << CData.GetArgument(1);
    return true;
}

bool Commands::Rename(const CommandLineData& CData)
{
    const std::string firstFile = CData.GetArgument(1);
    const std::string secondFile = CData.GetArgument(2);

    if(CData.GetLength() < 3)
    {
        return Authentication::CommandLineCheck(3, CData.GetLength());
    }
    else if ((CData.GetLength() == 3 && std::filesystem::is_directory(CData.GetArgument(2))) || CData.GetLength() > 3)
    {
        return MoveToDirectory(CData);
    }
    else if (CData.GetLength() == 3 && (!Authentication::IsTextFile(firstFile) || !Authentication::IsTextFile(secondFile)))
    {
        std::cout << "One of a files in not a correct type of format file:" << firstFile << ", " << secondFile << '\n';
        return false;
    }
    std::filesystem::rename(firstFile, secondFile);
    return true;
}

bool Commands::MoveToDirectory(const CommandLineData& CData)
{
    std::string directory = CData.GetArgument(CData.GetLength() - 1);

    std::cout << directory << std::endl;

    if(std::filesystem::is_directory(directory) == false)
    {
        std::cout << "Last argument of a command is not a directory: " << directory << '\n';
        return false;
    }

    for(size_t i = 1; i < CData.GetLength() - 1; i++)
    {
        const std::string filesName = CData.GetArgument(i);
        if(std::filesystem::is_regular_file(filesName) == false || Authentication::IsTextFile(filesName) == false)
        {
            std::cout << "Cannot move the file: " << filesName << '\n'; 
        }else{
            std::filesystem::rename(filesName, directory + "\\" + filesName);
        }
    }
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

        if(file.is_open() == false)
        {
            std::cout << "Cannot read file: " << filesPath << '\n';
            return false;
        }

        while(std::getline(file, filesPath))
        {
            std::cout << filesPath << '\n';
        }
        file.close();
        return true;
    }
    else if(CData.GetLength() == 3)
    {
        std::ofstream file;

        if(CData.GetArgument(1).compare(">>") == 0)
            file.open(CData.GetArgument(2), std::ios::app);
        else if (CData.GetArgument(1).compare(">") == 0)
            file.open(CData.GetArgument(2), std::ios::trunc);
        else
        {
            std::cout << "Append mode is not specified: " << CData.GetArgument(1) << '\n';
            return false;
        }

        CommandLineData temp{CData};
        temp.ChangeToRead(1, temp.GetArgument(2));
        PrintContent(temp);

        std::string line;
        while(std::getline(std::cin, line))
            file << line << '\n';
        
        file.close();
        return true;
    }
    std::cout << "Not enought arguments for the command.\n";
    return false;
}

bool Commands::MakeDirectory(const CommandLineData& CData)
{
    if(!Authentication::CommandLineCheck(2, CData.GetLength()))
        return false;

    std::error_code er;
    if(std::filesystem::create_directories(CData.GetArgument(1), er) == false)
    {
        std::cout << "Filesystem library throws error: "<<er.message()<<'\n';
        return false;
    }
    return true;
}

bool Commands::RemoveDirectory(const CommandLineData& CData)
{
    if(CData.GetLength() != 2)
    {
        std::cout << "Not enought arguments for the command.\n";
        return false;
    }
    std::error_code er;
    if(std::filesystem::remove_all(CData.GetArgument(1), er) == false)
    {
        std::cout << "Filesystem library throws error: "<<er.message()<<'\n';
        return false;
    }
    return true;
}

bool Commands::ListFiles(const CommandLineData& CData)
{
    if(CData.GetLength() == 1)
    {
        const std::filesystem::path filesPath = std::filesystem::current_path();
        for(const auto& i : std::filesystem::directory_iterator(filesPath))
        {
            std::cout << i.path() << '\n';
        }
        return true;
    }
    else if (CData.GetLength() == 2)
    {
        const std::string filesFormat = CData.GetArgument(1);
        if(!Authentication::IsTextFile(filesFormat))
        {
            std::cout << "Listing of this file is not supported: "<< filesFormat <<"\n";
            return false;
        }

        const std::filesystem::path filesPath = std::filesystem::current_path();

        for(const auto& i : std::filesystem::directory_iterator(filesPath))
        {
            const std::string filesPath = i.path().string();
            const size_t CIndexOfDot = filesPath.rfind('.');

            if(CIndexOfDot == filesPath.length() || CIndexOfDot == std::string::npos)
                continue;
            
            const std::string filesType = filesPath.substr(CIndexOfDot);

            if(filesType.compare(filesFormat) == 0)
            {
                std::cout << i.path() << '\n';
            }
        }
        return true;
    }
    else{
        std::cout << "Not enought arguments for the command.\n";
        return false;
    }
}

bool Commands::FindFile(const CommandLineData& CData)
{

    if(!Authentication::CommandLineCheck(4, CData.GetLength()))
    {
        return false;   
    }

    std::filesystem::path directPath = CData.GetArgument(1);
    const std::string options = CData.GetArgument(2);
    const std::string filesName = CData.GetArgument(3);

    bool displayName = false;
    bool displayPath = false;

    if(directPath.compare(".") == 0)
    {
        directPath = std::filesystem::current_path();
    }
    if (!std::filesystem::exists(directPath) || !std::filesystem::is_directory(directPath))
    {
        std::cout << "Directories name is invalid: " << directPath << '\n';
        return false;
    }
    if (options.at(0) != '-')
    {
        std::cout << "Invalid second argument: " << options << '\n';
        return false;
    }
    else{
        if(options.compare("-name") == 0)
            displayName = true;
        else if(options.compare("-path") == 0)
            displayPath = true;
        else
        {
            std::cout << "Invalid dash options: "<< options << '\n';
            return false;
        }
    }

    const std::string path = LoopDirectory(directPath, filesName);
    if(!path.empty())
    {
        if(displayName)
        {
            const size_t index = path.rfind("\\");
            std::cout << path.substr(index + 1) << '\n';
        }
        else if(displayPath)
            std::cout << path << '\n';
        return true;
    }
    std::cout << "File is not found." << path << '\n';
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
        else if (std::filesystem::is_regular_file(filesOrDirecPath) && Authentication::IsTextFile(filesOrDirecPath.string()))
        {
            if (filesOrDirecPath.filename().string() == fileName)
                return filesOrDirecPath.string();
        }
    }
    
    return std::string("");
}
