#include <iostream>
#include <print>
#include <functional>
#include <ranges>

#include "window.h"

#include "exception.h"



int main(){
 
    try{
    
        game::AutoRelease<int> autorel4 = game::AutoRelease<int>(16,nullptr);
        autorel4 = game::AutoRelease<int>(17,nullptr);


        game::Window win(800u,600u);
        while(win.running()){
        
        }

    }catch (const game::Exception& e){
        std::println(std::cerr,"{}",e);
    }
    catch(...){
        std::println(std::cerr,"unknown error!");
    }

    return 0;
}