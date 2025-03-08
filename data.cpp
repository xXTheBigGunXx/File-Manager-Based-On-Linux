#include "data.h"
#include <cstring>

CommandLineData::CommandLineData(int argc, char* argv[])
{
    len = static_cast<size_t>(argc - 1);
    data = new char*[len];

    for(size_t i = 0; i < len; i++)
    {
        data[i] = new char[strlen(argv[i + 1]) + 1];
        strcpy(data[i], argv[i + 1]);
    }
}

CommandLineData::~CommandLineData()
{
    for(size_t i = 0; i < len ;i++)
    {
        delete[] data[i];
    }
    delete[] data;
}

const char* CommandLineData::GetArgument(int index) const
{
    if(index < 0 || this->len <= index)
    {
        return nullptr;
    }

    return this->data[index];
}

size_t CommandLineData::GetLength() const
{
    return this->len;
}