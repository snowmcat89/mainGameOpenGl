#pragma once
#include <Windows.h>
#include <cstdint>
#include "auto_release.h"
#include "error.h"

namespace game{
    class Window{
        public:
            Window(std::int32_t width, std::int32_t height);
            ~Window() = default;

            Window(const Window&) = delete;
            auto operator=(const Window&) -> Window& = delete;


            Window(Window&&) = default;
            auto operator=(Window&&) -> Window& = default;

            auto running() const -> bool;

        private:
        game::AutoRelease<HWND,nullptr> window_;
        ::WNDCLASSA wc_;
    };
}