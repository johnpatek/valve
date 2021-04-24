#ifndef __VALVE_CONTROLLER_H__
#define __VALVE_CONTROLLER_H__
#include "common.h"

#include <protocol/message.h>

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

    void valve_stat(response_callback_type response_callback);

    void valve_log(response_callback_type response_callback);

private:
    template<int RequestType> void valve_request(
        response_callback_type on_response)
    {
        std::shared_ptr<protocol::request> request;
        std::shared_ptr<protocol::response> response;
        bool error(false);

        try
        {
            request = std::make_shared<protocol::request>(RequestType);
            process(request,response);
        }
        catch(const std::exception& e)
        {
            error = true;
            on_response(false,e.what());
        }

        if(!error)
        {
            on_response(
                response->get_status(),
                response->get_message());
        }
    }

    void process(
        const std::shared_ptr<protocol::request>& request, 
        std::shared_ptr<protocol::response>& response);
};

}

#endif