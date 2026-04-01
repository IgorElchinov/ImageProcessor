project(image_processor)

# Source files
set(SRC_CORE
    src/core/application.cpp
    src/core/bmp.cpp
    src/core/factory.cpp
    src/core/matrix.cpp
    src/core/parse.cpp
    src/core/pipeline.cpp
    src/core/utils.cpp
)

# Filters
set(SRC_FILTERS
    src/filters/base_filter.cpp
    src/filters/crop.cpp
    src/filters/edge_detection.cpp
    src/filters/gaussian_blur.cpp
    src/filters/grayscale.cpp
    src/filters/negative.cpp
    src/filters/sharpening.cpp
    src/filters/compress.cpp
)

# Main program

add_executable(image_processor
    image_processor.cpp
    ${SRC_CORE}
    ${SRC_FILTERS}
)

target_include_directories(image_processor PRIVATE
    src/core
    src/filters
)

