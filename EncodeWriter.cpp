#include "EncodeWriter.h"
#include "Writer.h"
#include "Reader.h"
#include "Writer.h"
#include <fstream>

const uint16_t FILE_NAME_END = 256;
const uint16_t ONE_MORE_FILE = 257;
const uint16_t ARCHIVE_END = 258;
const uint16_t MAX_CHAR = (1 << 9);

EncodeWriter::EncodeWriter(ArgsParser& arg_parser, uint16_t symbols_count, size_t max_symbols_code, Codes& codes,
                           size_t file_number)
    : arg_parser_(arg_parser),
      symbols_count_(symbols_count),
      max_symbols_code_(max_symbols_code),
      codes_(codes),
      file_number_(file_number) {
}

void EncodeWriter::Write(Writer& writer) {
    writer.PrintWord(symbols_count_);
    codes_.SortByCode();
    std::vector<uint16_t> number_of_codes_with_length(max_symbols_code_ + 1);
    std::vector<size_t> symbols_codes(MAX_CHAR);
    std::vector<size_t> symbols_lengths(MAX_CHAR);
    for (size_t i = 0; i < MAX_CHAR; ++i) {
        if (codes_[i].length == 0) {
            continue;
        }
        number_of_codes_with_length[codes_[i].length]++;
        writer.PrintWord(codes_[i].symbol);
        symbols_codes[codes_[i].symbol] = codes_[i].code;
        symbols_lengths[codes_[i].symbol] = codes_[i].length;
    }
    for (size_t i = 1; i < number_of_codes_with_length.size(); ++i) {
        writer.PrintWord(number_of_codes_with_length[i]);
    }
    for (size_t i = 0; i < arg_parser_[file_number_].size(); ++i) {
        unsigned char symbol = static_cast<unsigned char>(arg_parser_[file_number_][i]);
        writer.PrintCode(symbols_codes[symbol], symbols_lengths[symbol]);
    }
    writer.PrintCode(symbols_codes[FILE_NAME_END], symbols_lengths[FILE_NAME_END]);
    std::ifstream rstream(arg_parser_[file_number_], std::ios_base::in | std::ios_base::binary);
    if (!rstream.is_open()) {
        throw std::out_of_range("Cant open the file");
    }
    Reader reader(rstream);
    while (reader.HaveSomethingToRead()) {
        unsigned char symbol = reader.Get8bits();
        if (reader.HaveSomethingToRead()) {
            writer.PrintCode(symbols_codes[symbol], symbols_lengths[symbol]);
        }
    }
    if (file_number_ != arg_parser_.Size() - 1) {
        writer.PrintCode(symbols_codes[ONE_MORE_FILE], symbols_lengths[ONE_MORE_FILE]);
    } else {
        writer.PrintCode(symbols_codes[ARCHIVE_END], symbols_lengths[ARCHIVE_END]);
    }
}
