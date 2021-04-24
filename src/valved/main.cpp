#include <list>
#include <valve/host.h>
#include <toml.hpp>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/fmt/fmt.h>
#include "digital_pin.h"

namespace config_defaults
{
    const int THREADS(4);
    const int GPIO_PIN(21);
    const bool SIMULATE(true);
    const std::string LOG_PATH("/var/log/valve.log");
}

int main(int argc, char ** argv)
{
    std::shared_ptr<spdlog::logger> system_logger;
    std::string config_path;
    std::shared_ptr<toml::value> config;
    std::string log_path;
    std::shared_ptr<spdlog::logger> valve_logger;
    std::shared_ptr<valve::host> host;
    std::shared_ptr<digital_pin> pin;

    valve::open_callback_type open_callback(
        [&](bool& status, std::string& message)
        {
            if(!pin->get())
            {
                status = true;
                pin->set(true);
                valve_logger->info("Valve opened");    
            }
            else
            {
                message = "Valve is already open.";
                valve_logger->error(message);
            }
            valve_logger->flush();
        });

    valve::close_callback_type close_callback(
        [&](bool& status, std::string& message)
        {
            if(pin->get())
            {
                status = true;
                pin->set(false);
                valve_logger->info("Valve closed");
            }
            else
            {
                message = "Valve is already closed.";
                valve_logger->error(message);
            }
            valve_logger->flush();
        });

    valve::stat_callback_type stat_callback(
        [&](bool& status, std::string& message)
        {
            status = true;
            message = pin->get()?"Open":"Closed";
        });

    valve::log_callback_type log_callback(
        [&](bool& status,std::string& message)
        {
            status = true;
            std::list<std::string> log_entries;
            std::stringstream log_dump;
            std::fstream log_file(log_path,std::ios::in);
            for(std::string line_buffer;std::getline(log_file, line_buffer);)
            {
                log_entries.push_back(line_buffer);
                if(log_entries.size() > 10)
                {
                    log_entries.pop_front();
                }
            }
            for(const std::string& entry : log_entries)
            {
                log_dump << entry << std::endl;
            }
            message = log_dump.str();
        });

    system_logger = spdlog::syslog_logger_mt("system_logger");

    if(argc < 2)
    {
        system_logger->error("No config files.");
        system_logger->flush();
    }
    else
    {
        config_path = argv[1];
        try
        {
            toml::value config_root(toml::parse(config_path));
            
            config = std::make_shared<toml::value>(
                toml::find_or(
                    config_root,
                    "valved",
                    toml::value()));
            
            log_path = toml::find_or<toml::string>(
                *config,
                "LOG_PATH",
                config_defaults::LOG_PATH).str;

            valve_logger = spdlog::basic_logger_mt(
                "valve_logger",
                log_path);
            
            pin = std::make_shared<digital_pin>(
                toml::find_or<toml::integer>(
                    *config,
                    "GPIO_PIN",
                    config_defaults::GPIO_PIN),
                toml::find_or<toml::boolean>(
                    *config,
                    "SIMULATE",
                    config_defaults::SIMULATE));

            host = std::make_shared<valve::host>(
                open_callback,
                close_callback,
                stat_callback,
                log_callback);
            
            host->start();
        }
        catch(const std::exception& e)
        {
            system_logger->error(e.what());
            system_logger->flush();
            if(host.get() != nullptr)
            {
                host->stop();
            }
        }
        
    }
    
    return 0;
}