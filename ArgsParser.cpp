#include "ArgsParser.h"

ArgsParser::ArgsParser(size_t argc, char** argv) {
    for (size_t i = 0; i < argc; i++) {
        arguments_.push_back(argv[i]);
    }
}

bool ArgsParser::ContainArgument(const std::string& argument) const {
    return find(arguments_.begin(), arguments_.end(), argument) != arguments_.end();
}

std::string ArgsParser::operator[](size_t i) {
    return arguments_[i];
}

size_t ArgsParser::Size() const {
    return arguments_.size();
}
