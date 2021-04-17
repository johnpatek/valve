#ifndef __VALVE_COMMON_H__
#define __VALVE_COMMON_H__
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <thread>
#include <vector>

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>

#include <protocol/message.h>

namespace valve
{
#ifdef _WIN32
    using socket_type = SOCKET;
#else
    using socket_type = int;
#endif
    const socket_type INVALID_SOCKET = static_cast<
        const socket_type>(-1);
    const std::string SOCKET_NAME = "valve.sock";
    const std::string SOCKET_PATH = "/tmp/" + SOCKET_NAME;

    enum peer_types
    {
        CLIENT,
        SERVER
    };

    using unique_opaque = std::unique_ptr<void,std::function<void(void*)>>;

    socket_type open_unix_socket(int peer_type);
}

#endif