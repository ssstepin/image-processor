#pragma once

#include <exception>
#include <fstream>
#include <vector>
#include <string>

class ParserException : public std::exception {
public:
    explicit ParserException(const std::string& message);
    const char* what() const noexcept override;

private:
    std::string message_;
};

struct FilterConfig {
    std::string name;
    std::vector<std::string> arguments;

    bool Empty() const;
};

struct ParserResults {
    std::string input_path;
    std::string output_path;
    std::vector<FilterConfig> filters;
};

ParserResults Parse(int argc, char* argv[]);