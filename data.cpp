#include "data.h"
#include <cstring>

CommandLineData::CommandLineData(int argc, char* argv[])
{
    len = static_cast<size_t>(argc);
    data = new char*[len];
    for(size_t i = 0; i < len; i++)
    {
        data[i] = new char[strlen(argv[i] + 1)];
        strcpy(data[i], argv[i]);
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

char* CommandLineData::GetArgument(int index) const
{
    if(index < 0 || this->len <= index)
    {
        return nullptr;
    }

    char* argument = new char[this->len];
    strcpy(argument, this->data[index]);
    return argument;
}

size_t CommandLineData::GetLength() const
{
    return this->len;
}