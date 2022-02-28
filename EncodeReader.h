#pragma once

#include "ArgsParser.h"

class EncodeReader {
public:
    std::vector<size_t> GetSymbolFrequency();
    EncodeReader(ArgsParser& args_parser, size_t file_number);

private:
    ArgsParser args_parser_;
    size_t file_number_;
};
