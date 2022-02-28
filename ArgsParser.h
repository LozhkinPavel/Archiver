#pragma once

#include <string>
#include <vector>

class ArgsParser {
public:
    ArgsParser(size_t argc, char** argv);
    bool ContainArgument(const std::string& argument) const;
    std::string operator[](size_t i);
    size_t Size() const;

private:
    std::vector<std::string> arguments_;
};
