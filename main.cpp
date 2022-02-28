#include "ArgsParser.h"
#include "Reader.h"
#include "Codes.h"
#include "Trie.h"
#include "Writer.h"
#include "Encoder.h"
#include "EncodeReader.h"
#include "EncodeWriter.h"
#include "DecodeReader.h"
#include "DecodeWriter.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

void DoEncode(ArgsParser& args_parser) {
    std::ofstream stream(args_parser[2], std::ios_base::out | std::ios_base::binary);
    Writer writer(stream);
    for (size_t file_number = 3; file_number < args_parser.Size(); ++file_number) {
        EncodeReader encode_reader(args_parser, file_number);
        auto symbols_count = encode_reader.GetSymbolFrequency();
        Encoder encoder(args_parser, symbols_count, file_number);
        uint16_t symbol_count = 0;
        size_t max_symbols_code = 0;
        Codes symbols_code;
        encoder.Encode(symbol_count, max_symbols_code, symbols_code);
        EncodeWriter encode_writer(args_parser, symbol_count, max_symbols_code, symbols_code, file_number);
        encode_writer.Write(writer);
    }
}

void DoDecode(ArgsParser& arg_parser) {
    std::ifstream stream(arg_parser[2], std::ios_base::in | std::ios_base::binary);
    if (!stream.is_open()) {
        throw std::out_of_range("Cant open the file");
    }
    Reader reader(stream);
    while (true) {
        DecodeReader decode_reader(reader);
        Trie* book = decode_reader.GetBook();
        std::string file_name = decode_reader.GetFilename(book);
        DecodeWriter decode_writer(arg_parser);
        if (decode_writer.DecodeWrite(file_name, book, reader)) {
            break;
        }
    }
}

int main(int argc, char** argv) {
    ArgsParser args_parser(argc, argv);
    if (args_parser.ContainArgument("-h")) {
        std::cout << "archiver -c archive_name file1 [file2 ...] - заархивировать файлы"
                     " fil1, file2, ... и сохранить результат в файл archive_name"
                  << std::endl;
        std::cout << "archiver -d archive_name - разархивировать файлы из архива archive_name и положить в "
                     "текущую директорию. Имена файлов должны сохраняться при архивации и разархивации."
                  << std::endl;
        return 0;
    }

    if (args_parser.ContainArgument("-c")) {
        try {
            DoEncode(args_parser);
        } catch (const std::out_of_range& error) {
            std::cout << error.what();
        }
    }
    if (args_parser.ContainArgument("-d")) {
        if (args_parser.Size() > 3) {
            std::cout << "В аргументы функции напишите только имя архива" << std::endl;
            return 1;
        }
        try {
            DoDecode(args_parser);
        } catch (const std::out_of_range& error) {
            std::cout << error.what();
        }
    }
}
