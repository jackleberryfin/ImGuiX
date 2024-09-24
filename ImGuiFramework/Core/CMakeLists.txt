add_library(Core OBJECT
    ImGui.h
)

target_include_directories(Core
    PRIVATE
        include/Core
    PUBLIC
        include
)

target_link_libraries(Core 
    PRIVATE
        Basic
        Draw
)