#include "commandImplementation.h"

bool Commands::RemoveFiles(const CommandLineData& CData)
{

    for(size_t i = 1; i < CData.len; i++)
    {
        if(std::filesystem::remove(CData.GetArgument(i)) == false)
        {
            throw std::runtime_error("Files path is incorrect");
        }
    }
}