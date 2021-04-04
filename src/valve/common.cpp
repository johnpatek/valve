#include <valve/common.h>

namespace valve
{
    socket_type open_unix_socket()
    {
        socket_type result(INVALID_SOCKET);

        sockaddr_un name;

        result = socket(AF_UNIX,SOCK_STREAM,0);

        memset(&name,0,sizeof(sockaddr_un));

        name.sun_family = AF_UNIX;

        strncpy(
            name.sun_path, 
            SOCKET_PATH.c_str(), 
            sizeof(name.sun_path) - 1);

        if(connect(result,
            reinterpret_cast<sockaddr*>(&name),
            sizeof(sockaddr_un)))
        {
            throw std::runtime_error("Failed to connect socket");
        }

        return result;
    }
}