#ifndef __VALVE_HOST_H__
#define __VALVE_HOST_H__
#include "common.h"

namespace valve
{

class host
{
public:
    host();

    host(const host& copy) = delete;
    
    host(host&& move) = default;
    
    ~host();

    void start();

    void stop();

private:
    unique_opaque _event_base;

    unique_opaque _event_connection_listener;
};

}

#endif