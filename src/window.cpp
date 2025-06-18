#include "window.h"

namespace{

    bool g_running = true; 

    auto __stdcall def_win_proc(
     HWND   hWnd,
     UINT   Msg,
    WPARAM wParam,
 LPARAM lParam
)-> LRESULT {

    switch(Msg){
        case WM_CLOSE :{ g_running = false; break;}
        case WM_KEYDOWN: /* here when you press a key on keyboard, windows detect the key press
        at OS/HARDWARE level, then place a WM_KEYDOWN as a notification message
        queue , then the function just handle it so you can do whatever u want on that case*/
            std::println("key down!");
    }

    return ::DefWindowProc(hWnd,Msg,wParam,lParam);
}
}

namespace game{
    Window::Window(std::int32_t width, std::int32_t height): 
    window_({}),
    wc_({})
    {

        wc_ = {};
            wc_.lpfnWndProc = def_win_proc;
            wc_.hInstance = GetModuleHandle(nullptr);
            wc_.lpszClassName = "window class";
            wc_.style = CS_HREDRAW | CS_VREDRAW   | CS_OWNDC;
        
        ensure(::RegisterClassA(&wc_) != 0, "error for some reason");

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

    auto Window::Window::running() const -> bool{
        auto msg = ::MSG();
        while(::PeekMessageA(&msg,nullptr,0,0,PM_REMOVE) != 0){
            ::TranslateMessage(&msg);
            ::DispatchMessageA(&msg);
        }
        return g_running;
    }
}