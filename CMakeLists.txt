cmake_minimum_required(VERSION 3.15.0)

project(IMGUISample VERSION 0.1.0)

add_subdirectory(external)

add_executable(App main.cpp)
target_compile_features(App PRIVATE cxx_std_20)
target_link_libraries(App PRIVATE SDLWrap SDLImageWrap imgui imgui_SDL2Backend imgui_SDL2RendererBackend)

