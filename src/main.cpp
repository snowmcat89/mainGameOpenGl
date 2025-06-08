#include <print>
#include <functional>
#include <ranges>
#include "window.h"


int main(){
    //test
    game::AutoRelease<int> autorel4 = game::AutoRelease<int>(16,nullptr);
    autorel4 = game::AutoRelease<int>(17,nullptr);

    return 0;
}