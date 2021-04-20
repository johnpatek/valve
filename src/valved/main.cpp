#include <valve/host.h>
#include "board.h"
#include "config.h"
#include "log.h"

int main(int argc, char ** argv)
{
    std::shared_ptr<valve::host> host;
    bool open(false);

    valve::open_callback_type open_callback(
        [&](bool& status,std::string& message)
        {
            if(!open)
            {
                status = true;
                open = true;
            }
            else
            {
                message = "Valve is already open";
            }
        });

    valve::close_callback_type close_callback(
        [&](bool& status,std::string& message)
        {
            if(open)
            {
                status = true;
                open = false;
            }
            else
            {
                message = "Valve is already closed";
            }
        });

    valve::stat_callback_type stat_callback(
        [&](bool& status, std::string& message)
        {
            status = true;
            message = open?"Open":"Closed";
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