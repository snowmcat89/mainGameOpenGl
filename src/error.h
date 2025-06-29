#pragma once
#include "exception.h"
#include <format>
namespace game {
    template<class... Args>
    inline auto ensure(bool predicate, std::string_view msg, Args&&... args) -> void {
        if (!predicate)
            throw Exception(std::vformat(msg,std::make_format_args(std::forward(args)...)), 2u);
    }


    template<typename T,T invalid = T{}, typename... Args>
    auto ensure(AutoRelease<T,invalid>& obj, std::string_view msg, Args&&... args) -> void{
        ensure(!!obj, msg, std::forward<Args>(args)...);
        
    }

}
