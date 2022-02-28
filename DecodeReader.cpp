#include "DecodeReader.h"
#include "Codes.h"

Trie* DecodeReader::GetBook() {
    Codes codes;
    uint16_t symbol_count = reader_.GetWord();
    for (size_t i = 0; i < symbol_count; ++i) {
        uint16_t symbol = reader_.GetWord();
        codes[i].symbol = symbol;
    }
    uint16_t count_symbols = 0;
    size_t current_length = 1;
    while (count_symbols < symbol_count) {
        uint16_t symbols_with_current_length = reader_.GetWord();
        for (size_t i = count_symbols; i < count_symbols + symbols_with_current_length; ++i) {
            codes[i].length = current_length;
        }
        count_symbols += symbols_with_current_length;
        ++current_length;
    }
    codes.GetCodesByLength();
    Trie* root = new Trie(nullptr, nullptr, 0);
    for (size_t i = 0; i < MAX_CHAR; ++i) {
        if (codes[i].length == 0) {
            continue;
        }
        (*root).Add(codes[i].symbol, codes[i].code, codes[i].length);
    }
    return root;
}

std::string DecodeReader::GetFilename(Trie* book) {
    Trie* current_vertex = book;
    std::string file_name;
    uint16_t current_symbol = 0;
    while (true) {
        current_vertex = current_vertex->Move(reader_.GetBit());
        if (current_vertex->GetTerminal()) {
            current_symbol = current_vertex->GetSymbol();
            if (current_symbol == FILE_NAME_END) {
                break;
            }
            file_name.push_back(static_cast<unsigned char>(current_symbol));
            current_vertex = book;
        }
    }
    return file_name;
}
