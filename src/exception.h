#pragma once
#include <stdexcept>
#include <stacktrace>
#include <string>

namespace game{
    class Exception : public std::runtime_error{
        public:
            Exception(const std::string &what);
            auto stack_trace() const -> std::string;

        private:
            std::stacktrace trace_;
    };


}