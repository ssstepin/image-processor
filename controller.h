#pragma once

#include "io.h"
#include "parser.h"
#include "filters/blur.h"
#include "filters/crop.h"
#include "filters/edge.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharp.h"
#include "filters/wide.h"
#include <memory>
#include <vector>

std::shared_ptr<Filter> CreateFilterFromConfig(const FilterConfig &filter_config);

std::vector<std::shared_ptr<Filter>> CreateFilters(std::vector<FilterConfig> filters_configs);