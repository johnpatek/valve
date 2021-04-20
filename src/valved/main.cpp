#include <valve/host.h>
#include "digital_pin.h"
#include "config.h"
#include "log.h"

int main(int argc, char ** argv)
{
    std::shared_ptr<valve::host> host;
    std::shared_ptr<digital_pin> pin;
 
    valve::open_callback_type open_callback(
        [&](bool& status,std::string& message)
        {
            status = true;
            pin->set(true);
        });

    valve::close_callback_type close_callback(
        [&](bool& status,std::string& message)
        {
            status = true;
            pin->set(false); 
        });

    valve::stat_callback_type stat_callback(
        [&](bool& status, std::string& message)
        {
            status = true;
            message = pin->get()?"Open":"Closed";
        });

    valve::log_callback_type log_callback(
        [&](bool& status,std::string& message)
        {
            status = true;
            message = "Log not implemented";
        });

    try
    {
        host = std::make_shared<valve::host>(
            open_callback,
            close_callback,
            stat_callback,
            log_callback);

        pin = std::make_shared<digital_pin>(21);

        host->start();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        if(host.get() != nullptr)
        {
            host->stop();
        }
    }

    return 0;
}