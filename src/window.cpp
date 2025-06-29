#include "window.h"
#pragma comment(lib,"opengl32.lib")
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

auto resolve_wgl_functions(HINSTANCE hIncstance) -> void {
    auto wc = ::WNDCLASSA();
        wc.lpfnWndProc = ::DefWindowProc;
        wc.lpszMenuName = "dummy window";
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.hInstance = hIncstance;
    
    game::ensure(::RegisterClassA(&wc) == 0,"could not register dummy window");

    game::AutoRelease<HWND,nullptr> dummy_window = game::AutoRelease<::HWND,nullptr>{
        CreateWindowExA(
            0,
            wc.lpszClassName,
            wc.lpszClassName,
            0,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT, 
            0,0,wc.hInstance,0),::DestroyWindow};
    
    game::ensure(dummy_window,"couldn't create dummy window");

    auto dc = game::AutoRelease<::HDC>(::GetDC(dummy_window), [&dummy_window](auto dc){ ::ReleaseDC(dummy_window,dc);});
    game::ensure(dc,"couldn't create dc ");

    auto pfd = ::PIXELFORMATDESCRIPTOR();

    pfd.nSize = sizeof(::PIXELFORMATDESCRIPTOR);
    pfd.nSize = 1;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;


    auto pixel_format = ::ChoosePixelFormat(dc,&pfd);
    game::ensure(pixel_format != 0,"failed to choose pixel format");

    game::ensure(::SetPixelFormat(dc,pixel_format,&pfd),"couldn't set pixel format!");

    const auto context = game::AutoRelease<HGLRC>(::wglCreateContext(dc),::wglDeleteContext);
    game::ensure(context,"failed to create wglContext!");

    game::ensure(::wglMakeCurrent(dc,context),"error couldn't add current context");
    
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
        
        ensure(::RegisterClassA(&wc_) != 0, "backtrace_ error here! :");

        ::RECT rect{};
            rect.left = {};
            rect.right = static_cast<int>(width);
            rect.top = {}; rect.bottom = static_cast<int>(height);

         ensure(::AdjustWindowRect(&rect,WS_OVERLAPPEDWINDOW,false) != 0,"could not resize window");

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