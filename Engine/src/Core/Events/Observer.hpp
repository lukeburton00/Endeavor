#pragma once

class Observer
{
public:
    virtual void onNotify(void* data) = 0;
};