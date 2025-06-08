#include "window.h"

namespace game{
    Window::Window(std::int32_t width, std::int32_t height): 
    window_({})
    {

        ::RECT rect{.left = {}, .right = static_cast<int>(width),
         .top = {}, .bottom = static_cast<int>(height)};

         if(::AdjustWindowRect(&rect,WS_OVERLAPPEDWINDOW,false) == 0){
            throw std::runtime_error("could not resize window");
         }

        // window_ = {
        //     ::CreateWindowExA(
        //         0,"game window","game window",WS_OVERLAPPEDWINDOW,
        //         CW_USEDEFAULT,
        //         CW_USEDEFAULT,
        //         width,height,
                

        //     ), ::DestroyWindow};

    }
}