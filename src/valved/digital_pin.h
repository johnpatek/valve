#include <rpigpio/rpigpio.h>

class digital_pin
{
public:
    digital_pin(int pin, bool simulate);
    digital_pin(const digital_pin& copy) = delete;
    digital_pin(digital_pin&& copy) = default;
    ~digital_pin();
    bool get() const;  
    void set(bool value);
private:
    std::unique_ptr<GPIO::GPIOBase> _base;
    int _pin;
    bool _simulate;
    bool _sim_state;
};