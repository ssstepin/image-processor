add_executable(
        image_processor
        image_processor.cpp
        image.cpp filters/filter.cpp parser.cpp filters/sharp.cpp filters/edge.cpp filters/grayscale.cpp filters/negative.cpp filters/crop.cpp io.cpp controller.cpp filters/blur.cpp filters/wide.cpp)
