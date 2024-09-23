

add_library(Font OBJECT
    ImFont.cpp
)

target_include_directories(Font
    PRIVATE
        include/Font
    PUBLIC
        include
)

target_link_libraries(Font PUBLIC
    BasicTypes
)

