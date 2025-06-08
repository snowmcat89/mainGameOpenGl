#pragma once
#include <print>
#include <functional>
#include <ranges>

namespace game{
    template< class T, T Invalid = T{}>
    class AutoRelease{ // custom RAII for handling all stuff
        public:
        AutoRelease():
            AutoRelease({}, nullptr){}


         AutoRelease(T obj, std::function<void(T)> deleter):
            obj_(obj), deleter_(deleter) {}

        ~AutoRelease(){
            if (obj_ != Invalid && deleter_ != nullptr){
                deleter_(obj_);
            }
        }
        
        auto operator=(AutoRelease&& other) -> AutoRelease& {
            AutoRelease new_obj(std::move(other));
            swap(new_obj);
            return *this;
        }
        AutoRelease(AutoRelease&& other)
        : AutoRelease()
        {
            swap(other);
        }
        
        auto operator=(const AutoRelease&) -> AutoRelease & = delete;
        AutoRelease(const AutoRelease&) = delete;

        auto swap(AutoRelease& other) noexcept -> void{
            std::ranges::swap(this->obj_, other.obj_);
            std::ranges::swap(this->deleter_, other.deleter_);
        }

        T get() const { return obj_;};
        operator T() const { return obj_;};
        private:
        T obj_;
        std::function<void(T)> deleter_;
    };

}



