#ifndef __VALVE_CONTROLLER_H__
#define __VALVE_CONTROLLER_H__
#include "common.h"

namespace valve
{

class controller
{
public:
    controller(const std::string& name);
    
    controller(const controller& copy) = delete;

    controller(controller&& move);
    
    ~controller();

    template<class Rep,class Period>
    void valve_open(std::chrono::duration<Rep,Period> timeout)
    {

    }

    template<class Rep,class Period>
    void valve_close(std::chrono::duration<Rep,Period> timeout)
    {
        
    }

    void valve_status(std::string& status);

    void valve_log(std::vector<std::string>& messages, size_t count);

private:
    socket_type _socket;
    std::string _name;
};

}

#endif