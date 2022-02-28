#include "Writer.h"

extern const size_t WORD_LENGTH = 9;

void Writer::Flush() {
    char symbol = static_cast<char>(buffer);
    stream_.write(&symbol, 1);
    buffer = 0;
    buffer_size_ = 0;
}

Writer::~Writer() {
    Flush();
}

Writer::Writer(std::ostream& stream) : stream_(stream) {
}

void Writer::PrintCode(size_t code, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        if (buffer_size_ == 8) {
            Flush();
        }
        buffer += ((code >> (length - i - 1)) & 1) << (7 - buffer_size_);
        buffer_size_++;
    }
}

void Writer::PrintWord(uint16_t code) {
    for (size_t i = 0; i < WORD_LENGTH; ++i) {
        if (buffer_size_ == 8) {
            Flush();
        }
        buffer += ((code >> i) & 1) << (7 - buffer_size_);
        buffer_size_++;
    }
}

void Writer::Print8bits(unsigned char symbol) {
    for (size_t i = 0; i < 8; ++i) {
        if (buffer_size_ == 8) {
            Flush();
        }
        buffer += ((symbol >> i) & 1) << (buffer_size_);
        buffer_size_++;
    }
}
