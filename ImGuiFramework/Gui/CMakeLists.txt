

add_library(Gui OBJECT
    ImGuiStyle.cpp
)

target_include_directories(Gui
    PRIVATE
        include/Gui
    PUBLIC
        include
)

target_link_libraries(Gui PUBLIC
    BasicTypes
    Drawing
    Font
)

