#include "window.h"

namespace game{
    Window::Window(std::int32_t width, std::int32_t height): 
    window_({}),
    wc_({})
    {

        wc_ = {};
            wc_.style = CS_HREDRAW | CS_VREDRAW  | CS_OWNDC;
            wc_.lpfnWndProc = ::DefDlgProcA;
            wc_.hInstance = GetModuleHandle(nullptr);
            wc_.lpszClassName = "window class";
            
        

        if(::RegisterClassA(&wc_) == 0){
            throw std::runtime_error("failed to register class");
        }

        ::RECT rect{};
            rect.left = {};
            rect.right = static_cast<int>(width);
            rect.top = {}; rect.bottom = static_cast<int>(height);

         if(::AdjustWindowRect(&rect,WS_OVERLAPPEDWINDOW,false) == 0){
            throw std::runtime_error("could not resize window");
         }
        

        window_ = {
            ::CreateWindowExA(
                0,wc_.lpszClassName,"game window",WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                rect.right - rect.left, rect.bottom - rect.top,
                nullptr,
                nullptr,
                wc_.hInstance,
                nullptr
            ), ::DestroyWindow};

            ::ShowWindow(window_, SW_SHOW);
            ::UpdateWindow(window_);

    }
}