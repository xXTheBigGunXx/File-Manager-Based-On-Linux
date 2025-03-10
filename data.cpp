#include "data.h"

void CommandLineData::ChangeToRead()
{
    if(this->data.size() != 3)
        return;
    std::swap(this->data[1], this->data[2]);
    this->data.resize(2);
}

CommandLineData::CommandLineData(CommandLineData* copyData)
{
    this->data.assign(copyData->data.begin(), copyData->data.end());
}

CommandLineData::CommandLineData(int argc, char* argv[])
{
    this->data.reserve(static_cast<size_t>(argc - 1));

    for(size_t i = 1; i < static_cast<size_t>(argc); i++)  
    {
        this->data.push_back(std::string(argv[i]));
    }
}

CommandLineData::~CommandLineData()
{
    this->data.clear();
}

const std::string CommandLineData::GetArgument(int index) const
{
    if(index < 0 || this->data.size() <= index)
    {
        return std::string("");
    }

    return std::string(this->data[index]);
}

size_t CommandLineData::GetLength() const
{
    return this->data.size();
}