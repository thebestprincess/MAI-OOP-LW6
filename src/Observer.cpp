#include "../include/Observer.h"

void ConsoleObserver::on_kill(const std::string& killer, const std::string& victim)
{
    std::cout << "[LOG]: " << killer << " killed " << victim << std::endl;
}

FileObserver::FileObserver()
{
    file.open("../log.txt", std::ios::app);
}

FileObserver::~FileObserver()
{
    if (file.is_open())
    {
        file.close();
    }
}

void FileObserver::on_kill(const std::string& killer, const std::string& victim)
{
    if (file.is_open())
    {
        file << killer << " killed " << victim << std::endl;
    }
}