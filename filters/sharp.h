#pragma once

#include "filter.h"

class Sharpening : public FilterWithMatrix {
public:
    Sharpening();
    const RGBMatrix& GetFilterMatrix() const override;

private:
    const RGBMatrix sharp_matrix_ = {{{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}};
};