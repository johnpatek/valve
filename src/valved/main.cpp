#include <list>
#include <valve/host.h>
#include <toml.hpp>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/fmt/fmt.h>
#include "digital_pin.h"

int main(int argc, char ** argv)
{
    std::shared_ptr<spdlog::logger> system_logger;
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

    }
    else
    {

    }

    
    return 0;
}