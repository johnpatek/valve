
#include <valve/controller.h>

const size_t COMMAND_NAME_WIDTH = 15;
const size_t COMMAND_INFO_WIDTH = 25;

static void print_help();

static void response_callback(bool status, const std::string& message);

int main(int argc, char ** argv)
{
    std::shared_ptr<valve::controller> controller;
    if(argc > 1)
    {
        std::string command(argv[1]);
        controller = std::make_shared<valve::controller>();
        if(command == "open")
        {
            controller->valve_open(response_callback);
        }
        else if(command == "close")
        {   
            controller->valve_close(response_callback);
        }
        else if(command == "stat")
        {   
            controller->valve_stat(response_callback);
        }
        else if(command == "log")
        {
            controller->valve_log(response_callback);
        }
        else
        {
            std::cerr << "Error: \"" << command << "\" is not a valid command." << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: No command provided." << std::endl;
    }
    return 0;
}

void print_help()
{
    std::cerr << "valvectl - Command line interface for interacting with valve daemon" 
              << std::endl
              << std::endl
              << "open" << std::endl;
}

static void response_callback(bool status, const std::string& message)
{
    if(!status)
    {
        std::cerr << "Error: " << message;
    }
    else if(message.size() > 0)
    {
        std::cout << message << std::endl;
    }
}
