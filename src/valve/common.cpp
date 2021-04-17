#include <valve/common.h>

namespace valve
{
    socket_type open_unix_socket(int peer_type)
    {
        socket_type result(INVALID_SOCKET);

        sockaddr_un name;
        
        if(peer_type != peer_types::CLIENT 
            && peer_type != peer_types::SERVER)
        {
            throw std::runtime_error("Invalid peer type");
        }

        result = socket(AF_UNIX,SOCK_STREAM,0);

        memcpy(&name,0,sizeof(sockaddr_un));

        name.sun_family = AF_UNIX;

        strncpy(
            name.sun_path, 
            SOCKET_PATH.c_str(), 
            sizeof(name.sun_path) - 1);

        if(peer_type == peer_types::CLIENT)
        {
            if(connect(result,
                reinterpret_cast<sockaddr*>(&name),
                sizeof(sockaddr_un)))
            {
                throw std::runtime_error("Failed to connect socket");
            }
        }
        else
        {
            if(bind(
                result,
                reinterpret_cast<sockaddr*>(&name),
                sizeof(sockaddr_un)))
            {
                throw std::runtime_error("Failed to bind socket");
            }

            if(chmod(SOCKET_PATH.c_str(),0666))
            {
                std::cerr << "chmod failed" << std::endl;
            }
        }

        return result;
    }
}