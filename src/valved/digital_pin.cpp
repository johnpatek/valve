#include "digital_pin.h"

digital_pin::digital_pin(int pin) : _pin(pin)
{
    _base.mode(_pin,GPIO::GPIO_MODE::GPIO_OUTPUT);
}

digital_pin::~digital_pin()
{
    _base.mode(_pin,GPIO::GPIO_MODE::GPIO_INPUT);
}

bool digital_pin::get() const
{
    return _base.read(_pin);
}  

void digital_pin::set(bool value)
{
    _base.write(_pin,value);
}