#include <valve/host.h>

int main(int argc, char ** argv)
{
    std::shared_ptr<valve::host> host;

    try
    {
        host = std::make_shared<valve::host>();

        host->start();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        if(host.get() != nullptr)
        {
            host->stop();
        }
    }

    return 0;
}