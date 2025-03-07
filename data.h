#ifndef DATA_H
#define DATA_H
#include <cstddef>

class CommandLineData{
    private:
    size_t len;
    char** data;
    public:
    CommandLineData(int argc, char* argv[]);
    ~CommandLineData();
    const char* GetArgument(int index) const;
    size_t GetLength() const;
};

#endif