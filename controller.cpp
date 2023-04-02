#include "controller.h"

std::shared_ptr<Filter> CreateFilterFromConfig(const FilterConfig &config) {
    if (config.name == "crop") {
        if (config.arguments.size() != 2) {
            throw ParserException("wrong format for crop.");
        }
        size_t height = 0;
        size_t width = 0;
        try {
            height = std::stoull(config.arguments[0]);
            width = std::stoull(config.arguments[1]);
        } catch (std::invalid_argument &exc) {
            throw ParserException("invalid arguments for crop.");
        }
        return std::make_shared<Crop>(width, height);
    } else if (config.name == "gs") {
        if (!config.arguments.empty()) {
            throw ParserException("invalid arguments for grayscale.");
        }
        return std::make_shared<Grayscale>();
    } else if (config.name == "neg") {
        if (!config.arguments.empty()) {
            throw ParserException("invalid arguments for negative.");
        }
        return std::make_shared<Negative>();
    } else if (config.name == "sharp") {
        if (!config.arguments.empty()) {
            throw ParserException("invalid arguments for sharpening.");
        }
        return std::make_shared<Sharpening>();
    } else if (config.name == "edge") {
        if (config.arguments.size() != 1) {
            throw ParserException("wrong format for edge.");
        }
        double threshold = 0.0;
        try {
            threshold = std::stod(config.arguments[0]);
        } catch (std::invalid_argument &exc) {
            throw ParserException("invalid arguments for edge.");
        }
        return std::make_shared<Edge>(threshold);
    } else if (config.name == "blur") {
        if (config.arguments.size() != 1) {
            throw ParserException("wrong format for blur.");
        }
        double sigma = 1.0;
        try {
            sigma = std::stod(config.arguments[0]);
        } catch (std::invalid_argument &exc) {
            throw ParserException("invalid arguments for blur.");
        }
        return std::make_shared<Blur>(sigma);
    } else if (config.name == "wide") {
        if (config.arguments.size() != 1) {
            throw ParserException("invalid arguments for wide.");
        }
        double wide_coeff = 1.0;
        try {
            wide_coeff = std::stod(config.arguments[0]);
        } catch (std::invalid_argument &exc) {
            throw ParserException("invalid arguments for wide.");
        }
        if (wide_coeff < 1.0) {
            throw ParserException("invalid arguments for wide.");
        }
        return std::make_shared<Wide>(wide_coeff);
    } else {
        throw ParserException("no such filter: " + config.name + ".");
    }
}

std::vector<std::shared_ptr<Filter>> CreateFilters(std::vector<FilterConfig> filters_configs) {
    std::vector<std::shared_ptr<Filter>> filters;
    for (const auto &config : filters_configs) {
        filters.push_back(CreateFilterFromConfig(config));
    }
    return filters;
}
