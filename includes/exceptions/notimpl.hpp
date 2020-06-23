#ifndef NOT_IMPL_HPP
#define NOT_IMPL_HPP

#include <iostream>
#include <exception>

namespace exceptions {
    class NotImplementedException : public std::logic_error {
        public:
            NotImplementedException (std::string errorMsg) : std::logic_error{errorMsg} {};
            NotImplementedException () : std::logic_error{"Function not yet implemented."} {};
    };
};

#endif // NOT_IMPL_HPP