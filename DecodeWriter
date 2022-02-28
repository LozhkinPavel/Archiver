#pragma once

#include "Trie.h"
#include "Writer.h"
#include "Reader.h"
#include "ArgsParser.h"

class DecodeWriter {
public:
    DecodeWriter(ArgsParser& args_parser) : args_parser_(args_parser){};
    bool DecodeWrite(const std::string& file_name, Trie* book, Reader& reader);

private:
    ArgsParser& args_parser_;
};
