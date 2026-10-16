add_library(common STATIC
        timing.cpp)
target_include_directories(common PUBLIC ${PROJECT_SOURCE_DIR})
