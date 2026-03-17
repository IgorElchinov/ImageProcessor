#ifndef SRC_CORE_FACTORY_H
#define SRC_CORE_FACTORY_H

#include <string>
#include <unordered_map>
#include <vector>

#include "base_filter.h"
#include "pipeline.h"
#include "parse.h"

namespace image_processor {

// Filter Factory class
class FilterFactory {
public:  // ===== Member types =====
    using MakeFilterPtr = BaseFilter* (*)(const FilterDescriptor&);
    using MakeFilterFunction = std::unordered_map<std::string, MakeFilterPtr>;

public:  // ===== Common member functions =====
    Pipeline CreatePipeline(const Parser::DescriptorCollection& descriptors) const;

public:  // ===== Member constants =====
    static const MakeFilterFunction MAKE_FILTER;
};

}  // namespace image_processor

#endif  // SRC_CORE_FACTORY_H