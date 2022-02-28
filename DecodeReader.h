#pragma once
#include "ArgsParser.h"
#include "Trie.h"
#include "Reader.h"

const uint16_t FILE_NAME_END = 256;
const uint16_t MAX_CHAR = (1 << 9);

class DecodeReader {
public:
    DecodeReader(Reader& reader) : reader_(reader){};
    Trie* GetBook();
    std::string GetFilename(Trie* book);

private:
    Reader& reader_;
};
