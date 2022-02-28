#include "DecodeWriter.h"
#include <fstream>

const uint16_t FILE_NAME_END = 256;
const uint16_t ONE_MORE_FILE = 257;
const uint16_t ARCHIVE_END = 258;

bool DecodeWriter::DecodeWrite(const std::string& file_name, Trie* book, Reader& reader) {
    std::ofstream stream(file_name, std::ios_base::out | std::ios_base::binary);
    Writer writer(stream);
    Trie* current_vertex = book;
    uint16_t current_symbol = 0;
    while (true) {
        current_vertex = current_vertex->Move(reader.GetBit());
        if (current_vertex->GetTerminal()) {
            current_symbol = current_vertex->GetSymbol();
            if (current_symbol == ONE_MORE_FILE || current_symbol == ARCHIVE_END) {
                break;
            }
            writer.Print8bits(static_cast<unsigned char>(current_symbol));
            current_vertex = book;
        }
    }
    if (current_symbol == ARCHIVE_END) {
        return true;
    }
    return false;
}
