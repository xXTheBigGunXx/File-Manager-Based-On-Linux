#ifndef DATA_H
#define DATA_H
#include <cstddef>

class CommandLineData{
    public:
    size_t len;
    char** data;
    public:
    CommandLineData(int argc, char* argv[]);
    ~CommandLineData();
    char* GetArgument(int index) const;
    size_t GetLength() const;
};

#endif