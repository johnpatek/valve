#include <valve/common.h>
#include <toml/parser.hpp>

class config
{
public:
    config(const std::string path);
    config(const config& copy) = delete;
    config(config&& move) = default;

    std::string get_property(const std::string& key) const;
private:
    std::map<std::string,std::string> _config_data;
};