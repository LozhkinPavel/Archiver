#pragma once

#include <ostream>

class Writer {
public:
    ~Writer();
    void Flush();
    Writer(std::ostream& stream);
    void PrintCode(size_t code, size_t length);
    void PrintWord(uint16_t code);
    void Print8bits(unsigned char symbol);

private:
    std::ostream& stream_;
    unsigned char buffer = 0;
    size_t buffer_size_ = 0;
};
