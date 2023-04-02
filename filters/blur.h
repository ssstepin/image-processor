#pragma once

#include "filter.h"
#include <cmath>

class Blur : public Filter {
public:
    explicit Blur(double sigma);
    void Apply(Image *image) const override;

private:
    double blur_sigma_;
};