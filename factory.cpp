#include "factory.h"

#include <exception>
#include <stdexcept>

#include "filters.h"
#include "utils.h"

static const std::string CROP_FILTER_NAME = "crop";
static const size_t CROP_PARAMS_COUNT = 2;

static void CheckDescriptorCrop(const image_processor::FilterDescriptor& d) {
    if (d.name != CROP_FILTER_NAME) {
        throw std::invalid_argument("Filter name mismatch: crop expected.");
    }
    if (d.params.size() != CROP_PARAMS_COUNT) {
        throw image_processor::utils::InvalidDescriptor("Wrong number of parameters for crop: 2 expected.");
    }
    for (size_t i = 0; i < CROP_PARAMS_COUNT; ++i) {
        if (!image_processor::utils::IsInt(d.params[i])) {
            throw image_processor::utils::InvalidDescriptor(
                "Wrong type for 1 parameter of crop: integer number expected.");
        }
        int32_t val = std::stoi(d.params[i]);
        if (val < 0) {
            throw image_processor::utils::InvalidDescriptor(
                "Wrong value for 2 parameter of crop: should be non-negative.");
        }
    }
}

static image_processor::BaseFilter* MakeCrop(const image_processor::FilterDescriptor& d) {
    CheckDescriptorCrop(d);
    return new image_processor::Crop(std::stoi(d.params[1]), std::stoi(d.params[0]));
}

static const std::string EDGE_FILTER_NAME = "edge";
static const size_t EDGE_PARAMS_COUNT = 1;

static void CheckDescriptorEdge(const image_processor::FilterDescriptor& d) {
    if (d.name != EDGE_FILTER_NAME) {
        throw std::invalid_argument("Filter name mismatch: edge expected.");
    }
    if (d.params.size() != EDGE_PARAMS_COUNT) {
        throw image_processor::utils::InvalidDescriptor("Wrong number of parameters for edge: 1 expected.");
    }
    if (!image_processor::utils::IsFloat(d.params[0])) {
        throw image_processor::utils::InvalidDescriptor("Wrong type for 1 parameter of edge: float number expected.");
    }
    double val = std::stod(d.params[0]);
    if (val < 0 || val > 1) {
        throw image_processor::utils::InvalidDescriptor(
            "Wrong value for 1 parameter of edge: should be a fraction between 0 and 1.");
    }
}

static image_processor::BaseFilter* MakeEdge(const image_processor::FilterDescriptor& d) {
    CheckDescriptorEdge(d);
    return new image_processor::EdgeDetection(std::stod(d.params[0]));
}

static const std::string BLUR_FILTER_NAME = "blur";
static const size_t BLUR_PARAMS_COUNT = 1;

static void CheckDescriptorBlur(const image_processor::FilterDescriptor& d) {
    if (d.name != BLUR_FILTER_NAME) {
        throw std::invalid_argument("Filter name mismatch: blur expected.");
    }
    if (d.params.size() != BLUR_PARAMS_COUNT) {
        throw image_processor::utils::InvalidDescriptor("Wrong number of parameters for blur: 1 expected.");
    }
    if (!image_processor::utils::IsFloat(d.params[0])) {
        throw image_processor::utils::InvalidDescriptor("Wrong type for 1 parameter of blur: float number expected.");
    }
    double val = std::stod(d.params[0]);
    if (val < 0) {
        throw image_processor::utils::InvalidDescriptor(
            "Wrong value for 1 parameter of blur: should be non-negative number.");
    }
}

static image_processor::BaseFilter* MakeBlur(const image_processor::FilterDescriptor& d) {
    CheckDescriptorBlur(d);
    return new image_processor::GaussianBlur(std::stod(d.params[0]));
}

static const std::string GS_FILTER_NAME = "gs";
static const size_t GS_PARAMS_COUNT = 0;

static void CheckDescriptorGS(const image_processor::FilterDescriptor& d) {
    if (d.name != GS_FILTER_NAME) {
        throw std::invalid_argument("Filter name mismatch: gs expected.");
    }
    if (d.params.size() != GS_PARAMS_COUNT) {
        throw image_processor::utils::InvalidDescriptor("Wrong number of parameters for gs: 0 expected.");
    }
}

static image_processor::BaseFilter* MakeGS(const image_processor::FilterDescriptor& d) {
    CheckDescriptorGS(d);
    return new image_processor::Grayscale();
}

static const std::string NEG_FILTER_NAME = "neg";
static const size_t NEG_PARAMS_COUNT = 0;

static void CheckDescriptorNeg(const image_processor::FilterDescriptor& d) {
    if (d.name != NEG_FILTER_NAME) {
        throw std::invalid_argument("Filter name mismatch: neg expected.");
    }
    if (d.params.size() != NEG_PARAMS_COUNT) {
        throw image_processor::utils::InvalidDescriptor("Wrong number of parameters for neg: 0 expected.");
    }
}

static image_processor::BaseFilter* MakeNeg(const image_processor::FilterDescriptor& d) {
    CheckDescriptorNeg(d);
    return new image_processor::Negative();
}

static const std::string SHARP_FILTER_NAME = "sharp";
static const size_t SHARP_PARAMS_COUNT = 0;

static void CheckDescriptorSharp(const image_processor::FilterDescriptor& d) {
    if (d.name != SHARP_FILTER_NAME) {
        throw std::invalid_argument("Filter name mismatch: sharp expected.");
    }
    if (d.params.size() != SHARP_PARAMS_COUNT) {
        throw image_processor::utils::InvalidDescriptor("Wrong number of parameters for sharp: 0 expected.");
    }
}

static image_processor::BaseFilter* MakeSharp(const image_processor::FilterDescriptor& d) {
    CheckDescriptorSharp(d);
    return new image_processor::Sharpening();
}

const image_processor::FilterFactory::MakeFilterFunction image_processor::FilterFactory::MAKE_FILTER = {
    {"neg", MakeNeg}, {"crop", MakeCrop}, {"gs", MakeGS}, {"sharp", MakeSharp}, {"edge", MakeEdge}, {"blur", MakeBlur},
    // {"compress", image_processor::Compress::Make},  {"decompress", image_processor::Decompress::Make},
};

image_processor::Pipeline image_processor::FilterFactory::CreatePipeline(
    const Parser::DescriptorCollection& descriptors) const {
    Pipeline pl;
    for (const FilterDescriptor& d : descriptors) {
        MakeFilterFunction::const_iterator make_filter = MAKE_FILTER.find(d.name);
        if (make_filter == MAKE_FILTER.end()) {
            throw image_processor::utils::InvalidDescriptor("Unknown filter.");
        }
        BaseFilter* f = make_filter->second(d);
        if (!f) {
            throw std::runtime_error("Unexpected error while creating filter.");
        }
        pl.Add(f);
    }
    return pl;
}