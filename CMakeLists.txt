project(image_processor)

# Source files
set(SRC_CORE
    application.cpp
    bmp.cpp
    factory.cpp
    matrix.cpp
    parse.cpp
    pipeline.cpp
    utils.cpp
)

# Filters
set(SRC_FILTERS
    base_filter.cpp
    crop.cpp
    edge_detection.cpp
    gaussian_blur.cpp
    grayscale.cpp
    negative.cpp
    sharpening.cpp
    compress.cpp
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

