#ifndef SRC_CORE_PIPELINE_H
#define SRC_CORE_PIPELINE_H

#include <vector>

#include "base_filter.h"
#include "bmp.h"

namespace image_processor {

// Class for pipeline of filters
class Pipeline {
public:  // ===== Constructors & destructor =====
    Pipeline() = default;

    // Deleted because pipeline cannot be copied
    Pipeline(const Pipeline& other) = delete;

    Pipeline(Pipeline&& other) = default;

    // Deleted because pipeline cannot be copied
    Pipeline& operator=(const Pipeline& other) = delete;

    Pipeline& operator=(Pipeline&& other) = default;
    ~Pipeline();

public:  // ===== Common member functions =====
    // Adds filters to the collection
    void Add(BaseFilter* flt) {
        filters_.push_back(flt);
    }

    // Applies pipline to `img`
    BMPImage& Apply(BMPImage& img) const;

public:  // ===== Getters =====
    const std::vector<BaseFilter*> GetFilterCollection() const {
        return filters_;
    }

protected:  // ===== Private members =====
    std::vector<BaseFilter*> filters_;
};

}  // namespace image_processor

#endif  // SRC_CORE_PIPELINE_H