add_library(ImGuiDemoContent SHARED
    imgui_demo.cpp
)

install(TARGETS ImGuiDemoContent 
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# add_subdirectory(examples/example_${ImGuiPlatform_Option}_${ImguiRenderer_Option})