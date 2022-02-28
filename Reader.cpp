#include "Reader.h"

void Reader::Flush() {
    if (HaveSomethingToRead()) {
        char symbol = 0;
        stream_.read(&symbol, 1);
        buffer = static_cast<unsigned char>(symbol);
        buffer_size_ = 8;
        return;
    }
    throw std::out_of_range("Can't read file");
}

Reader::Reader(std::istream& stream) : stream_(stream) {
}

bool Reader::HaveSomethingToRead() {
    return !stream_.eof();
}

unsigned char Reader::Get8bits() {
    unsigned char answer = 0;
    for (size_t i = 0; i < 8; ++i) {
        if (buffer_size_ == 0) {
            Flush();
        }
        answer += (1 << i) * ((buffer >> (8 - buffer_size_)) & 1);
        --buffer_size_;
    }
    return answer;
}

bool Reader::GetBit() {
    bool answer = false;
    if (buffer_size_ == 0) {
        Flush();
    }
    answer = ((buffer >> (buffer_size_ - 1)) & 1);
    --buffer_size_;
    return answer;
}

uint16_t Reader::GetWord() {
    uint16_t answer = 0;
    for (size_t i = 0; i < WORD_LENGTH; ++i) {
        if (buffer_size_ == 0) {
            Flush();
        }
        answer += (1 << i) * ((buffer >> (buffer_size_ - 1)) & 1);
        --buffer_size_;
    }
    return answer;
}
