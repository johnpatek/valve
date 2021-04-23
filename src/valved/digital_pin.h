#include <rpigpio/rpigpio.h>

class digital_pin
{
public:
    digital_pin(int pin);
    ~digital_pin();
    bool get() const;  
    void set(bool value);
private:
    //GPIO::GPIOBase _base;
    int _pin;
};