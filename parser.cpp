#include "parser.h"

ParserException::ParserException(const std::string& message) {
    message_ = "Parser exception. Message: " + message;
}
const char* ParserException::what() const noexcept {
    return message_.c_str();
}

bool FilterConfig::Empty() const {
    return name.empty() && arguments.empty();
}

ParserResults Parse(int argc, char* argv[]) {
    ParserResults parser_results;
    if (argc < 3) {
        throw ParserException("not enough arguments.");
    }
    parser_results.input_path = argv[1];
    parser_results.output_path = argv[2];
    auto input_file = std::fopen(parser_results.input_path.c_str(), "r");
    if (!input_file) {
        throw ParserException("no such file: " + parser_results.input_path + ".");
    }
    if (parser_results.input_path.substr(parser_results.input_path.find_last_of(".") + 1) != "bmp") {
        throw ParserException("wrong file format. Expected .bmp.");
    }
    if (argc > 3) {
        FilterConfig config;
        for (int index = 3; index < argc; ++index) {
            if (argv[index][0] == '-') {
                if (!config.Empty()) {
                    parser_results.filters.push_back(config);
                }
                config.name = std::string(argv[index]).substr(1);
                config.arguments = {};
            } else {
                config.arguments.push_back(argv[index]);
            }
        }
        parser_results.filters.push_back(config);
    }
    return parser_results;
}