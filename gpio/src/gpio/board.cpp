#include <gpio/board.h>
#include <wiringPi.h>

namespace valve
{

namespace gpio
{

std::atomic<bool> board::_initialized(false);

std::atomic<int> board::_numbering_system(
    pins::numbering_systems::UNDEFINED);

void board::initialize(int numbering_system)
{
    _initialized.store(true);
    switch (numbering_system)
    {
        case pins::numbering_systems::WIRING_PI:
            wiringPiSetupGpio();
            break;
        case pins::numbering_systems::BROADCOM:
            wiringPiSetupGpio();
            break;
        case pins::numbering_systems::PHYSICAL:
            wiringPiSetupPhys();
            break;
        default:
            throw std::runtime_error(
                std::to_string(numbering_system) 
                + " is not a valid numbering system");
            break;
    }
    _numbering_system.store(numbering_system);
}

board::board(int numbering_system)
{
    if(!_initialized.load())
    {
        initialize(numbering_system);
    }

    if(_numbering_system.load() != numbering_system)
    {
        throw std::runtime_error(
            "Board numbering system does not match system");
    }
}

int digital_read(int pin)
{
    return digitalRead(pin);
}

void digital_write(int pin, int value)
{
    digitalWrite(pin,value);
}


}

}