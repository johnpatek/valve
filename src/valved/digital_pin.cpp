#include "digital_pin.h"

digital_pin::digital_pin(int pin, bool simulate) : 
    _pin(pin), 
    _simulate(simulate)
{
    if(_simulate)
    {
        _sim_state = false;
    }
    else
    {
        _base = std::make_unique<GPIO::GPIOBase>();
        _base->mode(_pin,GPIO::GPIO_MODE::GPIO_OUTPUT);
    }
}

digital_pin::~digital_pin()
{
    if(!_simulate)
    {
        _base->mode(_pin,GPIO::GPIO_MODE::GPIO_INPUT);
    }
}

bool digital_pin::get() const
{
    return (_simulate)?_sim_state:_base->read(_pin);
}  

void digital_pin::set(bool value)
{
    if(_simulate)
    {
        _sim_state = value;
    }
    else
    {
        _base->write(_pin,value);
    }
}