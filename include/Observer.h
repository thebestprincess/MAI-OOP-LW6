#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <fstream>
#include <iostream>

class IObserver
{
public:
    virtual void on_kill(const std::string& killer, const std::string& victim) = 0;
    virtual ~IObserver() = default;
};


class ConsoleObserver final: public IObserver
{
public:
    void on_kill(const std::string& killer, const std::string& victim) override;
};


class FileObserver final: public IObserver
{
    std::ofstream file;
public:
    FileObserver();
    ~FileObserver();

public:
    void on_kill(const std::string& killer, const std::string& victim) override; 
};

#endif // OBSERVER_H