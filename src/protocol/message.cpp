#include <json/json.h>
#include <protocol/message.h>

#define JSON(DATA) (reinterpret_cast<Json::Value*>(DATA))

static valve::unique_opaque construct_json()
{
    return std::move(
        valve::unique_opaque(new Json::Value(),[](void * data)
        {
            delete reinterpret_cast<Json::Value*>(data);
        }));
}

namespace protocol
{

request::request()
{
    _data = construct_json();
}

request::request(int command)
{
    _data = construct_json();
    set_command(command);
}

request::request(const uint8_t * const data, size_t size)
{
    _data = construct_json();
    parse(data,size);
}

bool request::has_command() const
{
    return (*JSON(_data.get()))["command"].isInt();
}

int request::get_command() const
{
    return (*JSON(_data.get()))["command"].asInt();
}

void request::set_command(int command)
{
    (*JSON(_data.get()))["command"] = command;
}

void request::parse(const uint8_t * const data, size_t size)
{
    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader(
        builder.newCharReader());
    std::string error;
    if(!reader->parse(
        reinterpret_cast<const char* const>(
            data), 
        reinterpret_cast<const char* const>(
            data + size),
        JSON(_data.get()),&error))
    {
        throw std::runtime_error(error);
    } 
}

std::string request::dump() const
{
    return std::move(
        JSON(_data.get())->toStyledString());
}


response::response()
{
    _data = construct_json();
}

response::response(bool status, const std::string& message)
{
    _data = construct_json();
    set_status(status);
    set_message(message);
}

response::response(bool status, std::string&& message)
{
    _data = construct_json();
    set_status(status);
    set_message(std::move(message));
}

response::response(const uint8_t * const data, size_t size)
{
    _data = construct_json();
    parse(data,size);
}

bool response::has_status() const
{
    return (*JSON(_data.get()))["status"].isBool();
}

bool response::get_status() const
{
    return (*JSON(_data.get()))["status"].asBool();
}

void response::set_status(bool status)
{
    (*JSON(_data.get()))["status"] = status;
}

bool response::has_message() const
{
    return (*JSON(_data.get()))["message"].isString();
}

std::string response::get_message() const
{
    return (*JSON(_data.get()))["message"].asString();
}

void response::set_message(const std::string& message)
{
    (*JSON(_data.get()))["message"] = message;
}

void response::set_message(std::string&& message)
{
    (*JSON(_data.get()))["message"] = std::move(message);
}

void response::parse(const uint8_t * const data, size_t size)
{
    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader(
        builder.newCharReader());
    std::string error;
    if(!reader->parse(
        reinterpret_cast<const char* const>(
            data), 
        reinterpret_cast<const char* const>(
            data + size),
        JSON(_data.get()),&error))
    {
        throw std::runtime_error(error);
    } 
}

std::string response::dump() const
{
    return std::move(
        JSON(_data.get())->toStyledString());
}

} 