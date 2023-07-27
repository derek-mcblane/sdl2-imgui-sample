#include "sdlpp.h"
#include "sdlpp_image.h"

#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include "imgui.h"

int main()
{
    sdl::Context global_setup{sdl::InitFlags::Video};
    sdl::image::Context global_image_setup{sdl::image::InitFlags::png};

    static constexpr sdl::Rectangle<int> screen_region{0, 0, 480, 480};
    static constexpr auto window_config = sdl::WindowConfig{
        .title = "IMGUI SDL Application",
        .x_position = SDL_WINDOWPOS_UNDEFINED,
        .y_position = SDL_WINDOWPOS_UNDEFINED,
        .width = screen_region.w,
        .height = screen_region.h,
        .flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE};
    static constexpr auto renderer_config =
        sdl::RendererConfig{.index = -1, .flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC};

    sdl::Window window{window_config};
    sdl::Renderer renderer{window.get_pointer(), renderer_config};

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // IF using Docking Branch

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window.get_pointer(), renderer.get_pointer());
    ImGui_ImplSDLRenderer2_Init(renderer.get_pointer());

    std::atomic_bool running{true};
    bool show_demo_window = true;
    while (running) {
        while (const auto event_result = sdl::poll_event()) {
            const SDL_Event& event = *event_result;
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
            }
        }
        if (window.shown()) {
            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
            ImGui::ShowDemoWindow(&show_demo_window);
            ImGui::Render();
            renderer.set_scale(io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
            renderer.set_draw_color(sdl::Color{0xFF, 0xFF, 0xFF, 0xFF});
            renderer.clear();
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
            renderer.present();
        }
    }

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
