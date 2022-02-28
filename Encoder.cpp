#include "Codes.h"
#include "Encoder.h"
#include "PriorityQueue.h"

const uint16_t FILE_NAME_END = 256;
const uint16_t ONE_MORE_FILE = 257;
const uint16_t ARCHIVE_END = 258;
const uint16_t MAX_CHAR = (1 << 9);

size_t GetCodesLength(Trie* root, size_t deep, std::vector<Codes::Code>& answer) {
    if (root == nullptr) {
        return 0;
    }
    if (root->GetTerminal()) {
        answer[root->GetSymbol()] = {root->GetSymbol(), 0, deep};
        return deep;
    }
    size_t deep1 = GetCodesLength(root->GetLeft(), deep + 1, answer);
    size_t deep2 = GetCodesLength(root->GetRight(), deep + 1, answer);
    return std::max(deep1, deep2);
}

Encoder::Encoder(ArgsParser& args_parser, std::vector<size_t>& symbols_count, size_t file_number)
    : args_parser_(args_parser), symbols_count_(symbols_count), file_number_(file_number) {
}

void Encoder::Encode(uint16_t& symbol_count, size_t& max_symbols_code, Codes& symbols_code) {
    symbols_count_[FILE_NAME_END] = 1;
    symbols_count_[ONE_MORE_FILE] = 1;
    symbols_count_[ARCHIVE_END] = 1;
    PriorityQueue vertexes;
    for (size_t i = 0; i < symbols_count_.size(); ++i) {
        if (symbols_count_[i] == 0) {
            continue;
        }
        vertexes.Push(new Trie(symbols_count_[i], true, i));
    }
    while (vertexes.Size() >= 2) {
        Trie* A = vertexes.Front();
        vertexes.Pop();
        Trie* B = vertexes.Front();
        vertexes.Pop();
        vertexes.Push(new Trie(B, A, A->GetValue() + B->GetValue()));
    }
    Trie* root = vertexes.Front();
    std::vector<Codes::Code> symbols_code_length(MAX_CHAR);
    max_symbols_code = GetCodesLength(root, 0, symbols_code_length);
    symbols_code = Codes({symbols_code_length});
    symbols_code.GetCodesByLength();
    symbol_count = symbols_code.SymbolCount();
}
