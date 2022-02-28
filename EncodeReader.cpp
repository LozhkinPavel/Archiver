#include "EncodeReader.h"
#include "Reader.h"
#include <fstream>

const uint16_t MAX_CHAR = (1 << 9);

EncodeReader::EncodeReader(ArgsParser& args_parser, size_t file_number)
    : args_parser_(args_parser), file_number_(file_number) {
}

std::vector<size_t> EncodeReader::GetSymbolFrequency() {
    std::vector<size_t> symbols_count(MAX_CHAR, 0);
    auto file_name = args_parser_[file_number_];
    for (size_t i = 0; i < file_name.size(); ++i) {
        ++symbols_count[static_cast<unsigned char>(file_name[i])];
    }
    std::ifstream stream(file_name, std::ios_base::in | std::ios_base::binary);
    if (!stream.is_open()) {
        throw std::out_of_range("Cant open the file");
    }
    Reader reader(stream);
    while (reader.HaveSomethingToRead()) {
        unsigned char symbol = reader.Get8bits();
        if (reader.HaveSomethingToRead()) {
            ++symbols_count[symbol];
        }
    }
    return symbols_count;
}
