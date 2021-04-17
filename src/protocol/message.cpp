#include <nlohmann/json.hpp>
#include <protocol/message.h>

#define TO_JSON(DATA) reinterpret_cast<nlohmann::json*>(DATA)

namespace protocol
{

request::request()
{
    _data = valve::unique_opaque(
        new nlohmann::json(),
        [](void * data)
        {
            nlohmann::json * ptr = TO_JSON(data);
            delete ptr;
        });
}

request::request(int command)
{

}

request::request(const uint8_t * const data, size_t size)
{

}

int request::get_command() const
{

}

void request::parse(const uint8_t * const data, size_t size)
{

}

std::string&& request::dump() const
{

}


}