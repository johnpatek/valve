#include <valve/common.h>

namespace protocol
{

enum commands
{
    OPEN,
    CLOSE,
    STATUS,
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

    int get_command() const;

    void set_command(int command);

    void parse(const uint8_t * const data, size_t size);

    std::string&& dump() const;   

private:
    valve::unique_opaque _data;
};

class response
{
public:
    response();

    response(bool status, const std::string& message);

    response(const uint8_t * const data, size_t size);

    response(const response& copy);

    response(response&& move);

    bool get_status() const;

    void set_status(bool status);

    std::string get_message() const;

    void set_message(const std::string& message);

    void set_message(std::string&& message);

    const std::string& get_message_view() const;

    void parse(const uint8_t * const data, size_t size);

    std::string&& dump() const;

private:
    valve::unique_opaque _data;
};

}