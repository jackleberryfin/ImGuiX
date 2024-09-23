add_library(BasicTypes OBJECT
    ImVec2.cpp
    ImBitArray.cpp
)

target_include_directories(BasicTypes
    PRIVATE
        include/Basic
    PUBLIC
        include
)

