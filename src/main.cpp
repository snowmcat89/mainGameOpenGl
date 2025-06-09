#include <iostream>
#include <print>
#include <functional>
#include <ranges>

#include "window.h"

#include "exception.h"

void boo(){
    throw game::Exception("error");
}

void foo(){
    boo();
}

int main(){
    //test
    // game::AutoRelease<int> autorel4 = game::AutoRelease<int>(16,nullptr);
    // autorel4 = game::AutoRelease<int>(17,nullptr);


    // game::Window win(800u,600u);
    // while(win.running()){
        
    // }

    try{
        foo();
    }catch (const game::Exception& e){
        std::println(std::cerr,"{}",e);
    }

    return 0;
}