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

set_target_properties(image_processor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# BMP test

add_executable(test_bmp
    test/test_bmp.cpp
    src/core/bmp.cpp
)

target_include_directories(test_bmp PRIVATE
    src/core
)

set_target_properties(test_bmp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Image IO test

add_executable(test_image_io
    test/test_image_io.cpp
    src/core/bmp.cpp
)

target_include_directories(test_image_io PRIVATE
    src/core
)

set_target_properties(test_image_io PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Parser test

add_executable(test_parser
    test/test_parser.cpp
    src/core/parse.cpp
)

target_include_directories(test_parser PRIVATE
    src/core
)

set_target_properties(test_parser PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Crop filter test

add_executable(test_crop
    test/test_crop.cpp
    ${SRC_CORE}
    ${SRC_FILTERS}
)

target_include_directories(test_crop PRIVATE
    src/core
    src/filters
)

set_target_properties(test_crop PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Base filter test

add_executable(test_base_filter
    test/test_base_filter.cpp
    ${SRC_FILTERS}
    test/test_utils.cpp
    src/core/bmp.cpp
    src/core/utils.cpp
)

target_include_directories(test_base_filter PRIVATE
    src/core
    src/filters
)

set_target_properties(test_base_filter PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Matrix test

add_executable(test_matrix
    test/test_matrix.cpp
    src/core/matrix.cpp
)

target_include_directories(test_matrix PRIVATE
    src/core
)

set_target_properties(test_matrix PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Negative filter test

add_executable(test_negative
    test/test_negative.cpp
    test/test_utils.cpp
    ${SRC_CORE}
    ${SRC_FILTERS}
)

target_include_directories(test_negative PRIVATE
    src/filters
    src/core
)

set_target_properties(test_negative PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Pipeline test

add_executable(test_pipeline
    test/test_pipeline.cpp
    src/filters/crop.cpp
    src/filters/negative.cpp
    test/test_utils.cpp
    src/core/bmp.cpp
    src/core/pipeline.cpp
)

target_include_directories(test_pipeline PRIVATE
    src/core
    src/filters
)

set_target_properties(test_pipeline PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

