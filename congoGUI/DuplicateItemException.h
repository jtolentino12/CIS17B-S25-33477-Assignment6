#ifndef DUPLICATEITEMEXCEPTION_H
#define DUPLICATEITEMEXCEPTION_H

#include <stdexcept>

class DuplicateItemException : public std::runtime_error {
public:
    DuplicateItemException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif // DUPLICATEITEMEXCEPTION_H
