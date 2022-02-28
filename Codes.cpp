#include "Codes.h"

const uint16_t MAX_CHAR = (1 << 9);

Codes::Codes() {
    codes_.resize(MAX_CHAR);
    for (size_t i = 0; i < MAX_CHAR; ++i) {
        codes_[i].symbol = i;
    }
}
Codes::Codes(std::vector<Code> &codes) : codes_(codes) {
}

Codes &Codes::operator=(const Codes &rhs) {
    codes_ = rhs.codes_;
    return (*this);
}

bool LengthCompare(const Codes::Code &lhs, const Codes::Code &rhs) {
    if (lhs.length != rhs.length) {
        return lhs.length < rhs.length;
    }
    return lhs.symbol < rhs.symbol;
}

bool CodeCompare(const Codes::Code &lhs, const Codes::Code &rhs) {
    if (lhs.length != rhs.length) {
        return lhs.length < rhs.length;
    }
    return lhs.code < rhs.code;
}

void Codes::GetCodesByLength() {
    std::vector<Code> sorted_codes = codes_;
    std::sort(sorted_codes.begin(), sorted_codes.end(), LengthCompare);
    size_t current_code = 0;
    Codes answer;
    for (size_t i = 0; i < sorted_codes.size(); ++i) {
        if (sorted_codes[i].length == 0) {
            codes_[i] = {sorted_codes[i].symbol, 0, 0};
            continue;
        }
        codes_[i] = {sorted_codes[i].symbol, current_code, sorted_codes[i].length};
        if (i != codes_.size() - 1) {
            current_code = (current_code + 1) << (sorted_codes[i + 1].length - sorted_codes[i].length);
        }
    }
}

uint16_t Codes::SymbolCount() {
    uint16_t answer = 0;
    for (size_t i = 0; i < codes_.size(); ++i) {
        if (codes_[i].length != 0) {
            ++answer;
        }
    }
    return answer;
}

Codes::Code &Codes::operator[](size_t i) {
    return codes_[i];
}

void Codes::SortByCode() {
    std::sort(codes_.begin(), codes_.end(), CodeCompare);
}
