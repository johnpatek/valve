#ifndef __VALVE_HOST_H__
#define __VALVE_HOST_H__
#include "common.h"
#include <protocol/message.h>

namespace valve
{

using request_callback_type = std::function<void(bool&,std::string&)>;
using open_callback_type = request_callback_type;
using close_callback_type = request_callback_type;
using stat_callback_type = request_callback_type;
using log_callback_type = request_callback_type;

class host
{
public:
    host(
        open_callback_type open_callback,
        close_callback_type close_callback,
        stat_callback_type stat_callback,
        log_callback_type log_callback);

    host(const host& copy) = delete;
    
    host(host&& move) = default;
    
    ~host();

    void process_request(
        const std::shared_ptr<protocol::request>& request,
        std::shared_ptr<protocol::response>& response);

    void start();

    void stop();

private:
    unique_opaque _event_base;

    unique_opaque _event_connection_listener;

    unique_opaque _signal_handler;

    open_callback_type _open_callback;

    close_callback_type _close_callback;

    stat_callback_type _stat_callback;
    
    log_callback_type _log_callback;
};

}

#endif