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

static void listener_callback(
    evconnlistener* listener,
    evutil_socket_t socket,
    sockaddr* saddr,
    int socklen,
    void* server)
{

}

static void signal_callback(
    evutil_socket_t sig, 
    short events, 
    void* server);

static void write_callback(
    bufferevent* event, 
    void* server)
{
    
}

static void read_callback(
    bufferevent* event, 
    void* connection);

static void event_callback(
    bufferevent*, 
    short, 
    void* server);

host::host()
{
    sockaddr_un addr;

    if(chmod(SOCKET_PATH.c_str(),0666))
    {
        std::cerr << "chmod 1 failed" << std::endl;
    }

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
                reinterpret_cast<sockaddr*>(&addr), 
                sizeof(sockaddr_un))),
        [](void* data)
        {
            evconnlistener_free(
                reinterpret_cast<evconnlistener*>(
                    data));
        });
        
}

host::~host()
{
    unlink(SOCKET_PATH.c_str());
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

}