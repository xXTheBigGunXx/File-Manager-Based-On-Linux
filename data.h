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
    ~CommandLineData() noexcept;
    inline const std::string GetArgument(int index) const noexcept
    {
        if(index < 0 || this->data.size() <= index)
        {
            return std::string("");
        }
        return std::string(this->data[index]);
    }
    inline size_t GetLength() const noexcept
    {
        return this->data.size();
    }
    void ChangeToRead(const size_t index, const std::string& newElement);
    void AddElement(const std::string& newElement);
    void ResizeDataVector(const size_t newSize);
};

#endif