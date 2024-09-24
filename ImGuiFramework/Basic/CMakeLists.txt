add_library(Basic OBJECT
    ImVec2.cpp
    ImBitArray.cpp
)

target_include_directories(Basic
    PRIVATE
        include/Basic
    PUBLIC
        include
)