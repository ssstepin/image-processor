#pragma once

#include "../image.h"

#include <vector>

class Filter {
public:
    virtual void Apply(Image* image) const;
    virtual ~Filter() = default;
};

class FilterWithMatrix : public Filter {
public:
    void Apply(Image* image) const override;
    virtual const RGBMatrix& GetFilterMatrix() const;
    FilterWithMatrix();

private:
    const RGBMatrix matrix_;
};