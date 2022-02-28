#pragma once
#include "ArgsParser.h"

class Encoder {
public:
    Encoder(ArgsParser& args_parser, std::vector<size_t>& symbols_count, size_t file_number);
    void Encode(uint16_t& symbol_count, size_t& max_symbols_code, Codes& symbols_code);

private:
    ArgsParser args_parser_;
    std::vector<size_t> symbols_count_;
    size_t file_number_;
};
