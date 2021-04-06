#ifndef __VALVE_COMMON_H__
#define __VALVE_COMMON_H__
#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>


namespace valve
{
#ifdef _WIN32
    using socket_type = SOCKET;
#else
    using socket_type = int;
#endif
    const std::string SOCKET_NAME = "valve.sock";
    const std::string SOCKET_PATH = "/tmp/" + SOCKET_NAME;

    enum peer_types
    {
        CLIENT,
        SOCKET
    };

    socket_type open_unix_socket(int peer_type);
}

#endif