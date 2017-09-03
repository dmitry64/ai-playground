#include "playground.hpp"

Playground::Playground()
{
    _threadActive.store(false);
}

Playground::~Playground()
{
    stop();
}

void Playground::init()
{
    _field.init();
}

void Playground::reset()
{
    _mutex.lock();
    _field.resetPositions();
    _mutex.unlock();
}

void Playground::start()
{
    if(!_threadActive.load()) {
        _threadActive.store(true);
        _thread = std::thread([this](){ this->run(); });
    }
}

void Playground::stop()
{
    if(_threadActive.load()) {
        _threadActive.store(false);
        _thread.join();
    }
}

void Playground::run()
{
    unsigned long int i = 0;
    while(_threadActive.load()) {
        //std::cout << "Tick: " << i << "\n";
        if(_mutex.try_lock()) {
            if(i > 8000000) {
                _field.evaluateResults();
                i = 0;
            }
            _field.simulatePhysics();
            _mutex.unlock();
            std::this_thread::sleep_for(std::chrono::nanoseconds(100));
        }
        ++i;
    }
}

Field Playground::requestField()
{
    _mutex.lock();
    Field temp(_field);
    _mutex.unlock();
    return temp;
}
