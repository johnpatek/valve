#include <valve/common.h>
#include <valve/host.h>
#include <event2/bufferevent_ssl.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/http.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/listener.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/keyvalq_struct.h>
#include <rpigpio/rpigpio.h>

namespace valve
{

static void signal_callback(
    evutil_socket_t sig, 
    short events, 
    void* server);

static void read_callback(
    bufferevent* buffer_event, 
    void* server);

static void event_callback(
    bufferevent* buffer_event, 
    short events, 
    void* server);

static void listener_callback(
    evconnlistener* listener,
    evutil_socket_t socket,
    sockaddr* saddr,
    int socklen,
    void* server);

host::host(
    open_callback_type open_callback,
    close_callback_type close_callback,
    stat_callback_type stat_callback,
    log_callback_type log_callback) : 
        _open_callback(open_callback), 
        _close_callback(close_callback), 
        _stat_callback(stat_callback), 
        _log_callback(log_callback)
{
    sockaddr_un name;

    memset(&name,0,sizeof(sockaddr_un));

    name.sun_family = AF_UNIX;

    strncpy(
        name.sun_path, 
        SOCKET_PATH.c_str(), 
        sizeof(name.sun_path) - 1);

    unlink(SOCKET_PATH.c_str());

    _event_base = unique_opaque(
        reinterpret_cast<void*>(event_base_new()),
        [](void* data)
        {
            event_base_free(
                reinterpret_cast<event_base*>(data));
        });

    _event_connection_listener = unique_opaque(
        reinterpret_cast<void*>(
            evconnlistener_new_bind(
                reinterpret_cast<event_base*>(
                    _event_base.get()),
                listener_callback,
                this,
                LEV_OPT_CLOSE_ON_FREE,
                100,
                reinterpret_cast<sockaddr*>(&name), 
                sizeof(sockaddr_un))),
        [](void* data)
        {
            evconnlistener_free(
                reinterpret_cast<evconnlistener*>(
                    data));
        });

    if(chmod(SOCKET_PATH.c_str(),0666) < 0)
    {
        throw std::runtime_error("Socket chmod failed");
    }

    _signal_handler = unique_opaque(
        evsignal_new(
            reinterpret_cast<event_base*>(
                _event_base.get()),
            SIGINT, 
            signal_callback, 
            this),
        [](void * data)
        {
            event_free(
                reinterpret_cast<event*>(data));
        });

    if(event_add(
        reinterpret_cast<event*>(
            _signal_handler.get()),nullptr) < 0)
    {
        throw std::runtime_error("Failed to create signal handler");
    }
}

host::~host()
{
    unlink(SOCKET_PATH.c_str());
}

void host::process_request(
        const std::shared_ptr<protocol::request>& request,
        std::shared_ptr<protocol::response>& response)
{
    bool status(false);
    std::string message;
    if(request->has_command())
    {
        switch (request->get_command())
        {
        case protocol::OPEN:
            _open_callback(status,message);
            break;
        
        case protocol::CLOSE:
            _close_callback(status,message);
            break;
        
        case protocol::STAT:
            _stat_callback(status,message);
            break;
        
        case protocol::LOG:
            _log_callback(status,message);
            break;
        default:
            message = "Invalid command.";
            break;
        }
    }
    response = std::make_shared<protocol::response>(
        status, message);
}

void host::start()
{
    event_base_dispatch(
        reinterpret_cast<event_base*>(
            _event_base.get()));
}

void host::stop()
{
    event_base_loopbreak(
        reinterpret_cast<event_base*>(
            _event_base.get()));
}


void signal_callback(
    evutil_socket_t sig, 
    short events, 
    void* server)
{
    reinterpret_cast<host*>(server)->stop();
}


void read_callback(
    bufferevent* buffer_event, 
    void* server)
{
    evbuffer * input;
    std::vector<uint8_t> request_buffer(1024);
    ssize_t read_size;
    std::shared_ptr<protocol::request> request;
    std::shared_ptr<protocol::response> response;
    std::string response_buffer;
    evbuffer * output;
    
    input = bufferevent_get_input(buffer_event);
    
    read_size = evbuffer_remove(
        input,
        request_buffer.data(),
        request_buffer.size());
    
    request = std::make_shared<protocol::request>(
        request_buffer.data(),
        read_size);
    
    reinterpret_cast<host*>(server)->process_request(
        request,response);
    
    response_buffer = response->dump();
    
    output = bufferevent_get_output(buffer_event);
    
    evbuffer_add(
        output,
        response_buffer.data(),
        response_buffer.size());
}

void event_callback(
    bufferevent* buffer_event, 
    short events, 
    void* server)
{
    if (events & BEV_EVENT_ERROR)
    {
        throw std::runtime_error("Error from bufferevent");
    }
    
    if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) 
    {
        bufferevent_free(buffer_event);
    }
}

void listener_callback(
    evconnlistener* listener,
    evutil_socket_t socket,
    sockaddr* saddr,
    int socklen,
    void* server)
{
    event_base * base;    
    bufferevent * buffer_event;

    base = evconnlistener_get_base(listener);
    buffer_event = bufferevent_socket_new(
        base,
        socket, 
        BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setcb(
        buffer_event,
        read_callback,
        nullptr,
        event_callback,
        server);
    bufferevent_enable(
        buffer_event, 
        EV_WRITE | EV_READ);
}

}