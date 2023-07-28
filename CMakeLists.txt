cmake_minimum_required(VERSION 3.21.0)

project(IMGUISample VERSION 0.1.0)

add_subdirectory(external)

add_executable(App WIN32 main.cpp)
target_compile_features(App PRIVATE cxx_std_20)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
if(TARGET SDL2::SDL2main)
    target_link_libraries(App PRIVATE SDL2::SDL2main)
endif()
target_link_libraries(App PRIVATE
    SDLWrap
    SDLImageWrap
    imgui
    imgui_SDL2Backend
    imgui_SDL2RendererBackend
)

install(TARGETS
    App
    CONFIGURATIONS Debug Release
    RUNTIME DESTINATION bin
)

