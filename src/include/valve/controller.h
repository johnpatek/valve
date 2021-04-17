#ifndef __VALVE_CONTROLLER_H__
#define __VALVE_CONTROLLER_H__
#include "common.h"

namespace valve
{

using response_callback_type = std::function<void(bool,const std::string&)>;

class controller
{
public:
    controller();

    controller(const controller& copy) = delete;

    controller(controller&& move) = default;

    void valve_open(response_callback_type response_callback);

    void valve_close(response_callback_type response_callback);

    void valve_status(response_callback_type response_callback);

    void valve_log(response_callback_type response_callback);

private:
    template<int RequestType> void valve_request(
        response_callback_type on_response)
    {
        protocol::request request(RequestType);
        protocol::response response;
        process(request,response);
        on_response(
            response.is_good(),
            response.get_message());
    }

    void process(
        const protocol::request& request, 
        protocol::response& response);
};

}

#endif