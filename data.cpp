#include "data.h"

void CommandLineData::ChangeToRead(const size_t index, const std::string& newElement)
{
    if(index < 0 || index >= this->GetLength())
        return;
    this->data[index] = newElement;
    this->data.resize(2);
}

void CommandLineData::AddElement(const std::string& newElement)
{
    this->data.push_back(newElement);
}

void CommandLineData::ResizeDataVector(const size_t newSize)
{
    if(newSize < 0 || newSize > this->GetLength())
        return;
    this->data.resize(newSize);
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