# Image processor

## Usage

    image_processor {input file} {output file} [-{filter 1} [filter argument 1] [filter argument 2] ...] [-{filter 2} [filter argument 1] [filter argument 2] ...] ...

## Currently available filters:

    -crop [width] [height] -- crops image to `height` x `wight` (must be two non-negative integers)
    -neg -- creates a negative of the image
    -gs -- creates black & white version of the image
    -sharp -- sharpens the image
    -edge [threshold] -- applies edge detection with given `threshold` (must be a float between 0 and 1)
    -blur [sigma] -- applies gaussian blur (`sigma` be a non-negative number)

## Current project architecture

```
/image_processor
├── CMakeLists.txt
├── image_processor.cpp
├── src/
│   ├── core/
│   │   ├── application.h / application.cpp
│   │   ├── bmp.h / bmp.cpp
│   │   ├── factory.h / factory.cpp
│   │   ├── matrix.h / matrix.cpp
│   |   ├── parse.h / parse.cpp
│   |   ├── pipeline.h / pipeline.cpp
│   │   └── utils.h / utils.cpp
│   └── filters/
│       ├── filters.h
│       ├── base_filter.h / base_filter.cpp
│       ├── crop.h / crop.cpp
│       ├── edge_detection.h / edge_detection.cpp
│       ├── gaussian_blur.h / gaussian_blur.cpp
│       ├── grayscale.h / grayscale.cpp
│       ├── negative.h / negative.cpp
│       └── sharpening.h / sharpening.cpp
└── test/ (Deleted because of linter check. See 'Implemented gaussian blur' commit)
    ├── test_utils.h / test_utils.cpp
    ├── test_base_filter.cpp
    ├── test_bmp.cpp
    ├── test_crop.cpp
    ├── test_image_io.cpp
    ├── test_matrix.cpp
    ├── test_negative.cpp
    ├── test_parser.cpp
    └── test_pipeline.cpp
```
