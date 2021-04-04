#ifndef __VALVE_GPIO_BOARD_H__
#define __VALVE_GPIO_BOARD_H__

#include <atomic>
#include <stdexcept>
#include <string>

namespace valve
{

namespace gpio
{
    namespace pins
    {
        enum numbering_systems
        {
            UNDEFINED,
            WIRING_PI,
            BROADCOM,
            PHYSICAL
        };
    }

    class board
    {
    public:
        board(int numbering_system);

        ~board() = default;

        static void initialize(int numbering_system);

        int digital_read(int pin);

        void digital_write(int pin, int value);

    private:
        static std::atomic<bool> _initialized;
        static std::atomic< int> _numbering_system;
    };
}

}

#endif