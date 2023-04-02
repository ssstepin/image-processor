#pragma once

#include "filter.h"

class Edge : public FilterWithMatrix {
public:
    explicit Edge(double threshold);
    const RGBMatrix &GetFilterMatrix() const override;
    void Apply(Image *image) const override;

private:
    const RGBMatrix edge_matrix_ = {{{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}};
    double threshold_;
};