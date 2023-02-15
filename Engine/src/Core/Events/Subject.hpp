#pragma once
#include <vector>
#include <memory>
#include "Observer.hpp"

class Subject
{
public:
    void addObserver(std::shared_ptr<Observer> observer);
    void removeObserver(std::shared_ptr<Observer> observer);

protected:
    void notify(void* data);
    std::vector<std::shared_ptr<Observer>> mObservers;
};