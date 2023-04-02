#pragma once

#include "filter.h"

class Wide : public Filter {
public:
    explicit Wide(double coeff);
    void Apply(Image *image) const override;

private:
    double wide_coeff_;
};