#pragma once

#include <istream>
#include <string>

const size_t WORD_LENGTH = 9;

class Reader {
public:
    Reader(std::istream& stream);
    bool HaveSomethingToRead();
    unsigned char Get8bits();
    uint16_t GetWord();
    void Flush();
    bool GetBit();

private:
    std::istream& stream_;
    unsigned char buffer = 0;
    size_t buffer_size_ = 0;
};
