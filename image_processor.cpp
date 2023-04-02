#include "io.h"
#include "parser.h"
#include "controller.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "--------------------------------------------------------------\n"
                     "                      IMAGE PROCESSOR                         \n"
                     "--------------------------------------------------------------\n"
                     "input_path output_path [-filter_name][filter_args]]           \n"
                     "-crop width height (Crop image)                               \n"
                     "-gs (Grayscale)                                               \n"
                     "-neg (Negative)                                               \n"
                     "-edge threshold (Edge detection)                              \n"
                     "-blur sigma (Gaussian blur with radius=sigma)                 \n"
                     "-wide coeff (Makes image wide with height = height / coeff, coeff >= 1)";
        return 0;
    }
    try {
        auto parse_args = Parse(argc, argv);
        auto filters = CreateFilters(parse_args.filters);
        std::ifstream input_stream(parse_args.input_path, std::ios::binary);
        std::ofstream output_stream(parse_args.output_path, std::ios::binary);
        BMPObject bmp_result(input_stream);
        for (const auto& filter : filters) {
            filter->Apply(bmp_result.GetImagePtr());
        }
        bmp_result.Write(output_stream);
    } catch (const ParserException& e) {
        std::cout << e.what();
    } catch (const BMPReaderException& e) {
        std::cout << e.what();
    }
}
