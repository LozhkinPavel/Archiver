#pragma once

#include "ArgsParser.h"
#include "Codes.h"
#include "Writer.h"

class EncodeWriter {
public:
    EncodeWriter(ArgsParser& arg_parser, uint16_t symbols_count, size_t max_symbols_code, Codes& codes,
                 size_t file_number);
    void Write(Writer& writer);

private:
    ArgsParser arg_parser_;
    uint16_t symbols_count_;
    size_t max_symbols_code_;
    Codes codes_;
    size_t file_number_;
};
