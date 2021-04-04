#ifndef __PROTOCOL_MESSAGE_H__
#define __PROTOCOL_MESSAGE_H__

#include <valve/common.h>

namespace protocol
{

enum commands
{
    OPEN,
    CLOSE,
    STAT,
    LOG
};

class request
{
public:
    request();

    request(int command);    

    request(const uint8_t * const data, size_t size);

    request(const request& copy) = delete;

    request(request&& move) = default;

    bool has_command() const;

    int get_command() const;

    void set_command(int command);

    void parse(const uint8_t * const data, size_t size);

    std::string dump() const;   

private:
    valve::unique_opaque _data;
};

class response
{
public:
    response();

    response(bool status, const std::string& message);

    response(bool status, std::string&& message);

    response(const uint8_t * const data, size_t size);

    response(const response& copy) = delete;

    response(response&& move) = default;

    bool has_status() const;

    bool get_status() const;

    void set_status(bool status);

    bool has_message() const;

    std::string get_message() const;

    void set_message(const std::string& message);

    void set_message(std::string&& message);

    void parse(const uint8_t * const data, size_t size);

    std::string dump() const;

private:
    valve::unique_opaque _data;
};

}

#endif