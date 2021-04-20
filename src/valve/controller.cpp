#include <valve/controller.h>

namespace valve
{
    controller::controller() {}

    void controller::valve_open(
        response_callback_type response_callback)
    {
        valve_request<protocol::OPEN>(response_callback);
    }

    void controller::valve_close(
        response_callback_type response_callback)
    {
        valve_request<protocol::CLOSE>(response_callback);
    }

    void controller::valve_stat(
        response_callback_type response_callback)
    {
        valve_request<protocol::STAT>(response_callback);
    }

    void controller::valve_log(
        response_callback_type response_callback)
    {
        valve_request<protocol::LOG>(response_callback);
    }

    void controller::process(
        const std::shared_ptr<protocol::request>& request, 
        std::shared_ptr<protocol::response>& response)
    {
        std::string request_buffer(request->dump());
        std::vector<uint8_t> response_buffer(1024);
        socket_type socket;
        ssize_t read_amount;

        socket = open_unix_socket();

        if(write(socket,request_buffer.data(),request_buffer.size()) < 0)
        {
            throw std::runtime_error("Failed to write to socket");
        }

        read_amount = read(
            socket,
            response_buffer.data(),
            response_buffer.size());

        if(read_amount < 0)
        {
            throw std::runtime_error("Failed to read from socket");
        }

        response = std::make_shared<protocol::response>(
            response_buffer.data(),
            read_amount);

        close(socket);
    }

}

