#pragma once

class Observable;

class Observer {
public:
    virtual void update(Observable* observable) = 0;
    virtual ~Observer() = default;
};