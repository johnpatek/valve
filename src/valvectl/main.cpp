
#include <valve/common.h>

const size_t COMMAND_NAME_WIDTH = 15;
const size_t COMMAND_INFO_WIDTH = 25;

static void print_help();

int main(int argc, char ** argv)
{
    
    print_help();
    return 0;
}

void print_help()
{
    std::cerr << "valvectl - Command line interface for interacting with valve daemon" 
              << std::endl
              << std::endl
              << "open" << std::endl;
}