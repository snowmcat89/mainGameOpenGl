#include "exception.h"

namespace game{
    Exception::Exception(const std::string &what): 
        std::runtime_error(what),
        trace_(std::stacktrace::current()){}
    
        
    auto Exception::stack_trace() const -> std::string{
        return std::to_string(trace_);
    }
}




