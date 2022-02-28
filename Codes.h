#pragma once

#include <cstdint>
#include <vector>

class Codes {
public:
    struct Code {
        uint16_t symbol;
        size_t code;
        size_t length;
    };
    Codes();
    Codes(std::vector<Code>& codes);
    uint16_t SymbolCount();
    void GetCodesByLength();
    void SortByCode();
    Code& operator[](size_t i);
    Codes& operator=(const Codes& rhs);

private:
    std::vector<Code> codes_;
};
