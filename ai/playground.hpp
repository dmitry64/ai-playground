#ifndef PLAYGROUND_HPP
#define PLAYGROUND_HPP

#include <field.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>

class Playground
{
    Field _field;
    std::thread _thread;
    std::atomic_bool _threadActive;
    std::mutex _mutex;
public:
    Playground();
    ~Playground();
    void init();
    void reset();
    void start();
    void stop();
    void run();
    Field requestField();

};

#endif // PLAYGROUND_HPP
