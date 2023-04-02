#pragma once

#include "filter.h"

class Grayscale : public Filter {
public:
    Grayscale();
    void Apply(Image *image) const override;

private:
    const std::vector<double> gray_effect_ = {0.299, 0.587, 0.114};
};