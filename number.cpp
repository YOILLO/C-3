#include "number.h"

Number::Number(int val) : value(val) {
    stringValue = std::to_string(val);
    std::cout << "Constructor called for value: " << value << std::endl;
}

Number::Number(const Number& other) : value(other.value), stringValue(other.stringValue) {
    std::cout << "Copy constructor called for value: " << value << std::endl;
}

Number::Number(Number&& other) noexcept : value(other.value), stringValue(std::move(other.stringValue)) {
    std::cout << "Move constructor called for value: " << value << std::endl;
}

Number::~Number() {
    std::cout << "Destructor called for value: " << value << std::endl;
}

Number& Number::operator=(const Number& other) {
    if (this != &other) {
        value = other.value;
        stringValue = other.stringValue;
        std::cout << "Copy assignment operator called for value: " << value << std::endl;
    }
    return *this;
}

Number& Number::operator=(Number&& other) noexcept {
    if (this != &other) {
        value = other.value;
        stringValue = std::move(other.stringValue);
        std::cout << "Move assignment operator called for value: " << value << std::endl;
    }
    return *this;
}

int Number::getValue() const {
    return value;
}

std::string Number::getStringValue() const {
    return stringValue;
}

void Number::display() const {
    std::cout << "Value: " << value << ", String Representation: " << stringValue << std::endl;
}

bool Number::operator==(const Number& other) const
{
    return value == other.getValue();
}
