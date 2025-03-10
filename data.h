#ifndef DATA_H
#define DATA_H

#include <cstddef>
#include <string>
#include <cstring>
#include <vector>

class CommandLineData{
    private:
    std::vector<std::string> data; 
    public:
    CommandLineData(int argc, char* argv[]);
    CommandLineData(CommandLineData* copyData);
    ~CommandLineData();
    const std::string GetArgument(int index) const;
    size_t GetLength() const;
    void ChangeToRead();
};

#endif