add_library(Drawing OBJECT
    ImDrawList.cpp
)

target_include_directories(Drawing
    PRIVATE
        include/Draw
    PUBLIC
        include
)

target_link_libraries(Drawing 
    PRIVATE
        BasicTypes
        Font
        Core
)