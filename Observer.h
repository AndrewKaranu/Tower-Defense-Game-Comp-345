#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual void update() = 0;  // Pure virtual function to be implemented by observers
    virtual ~Observer() {}      // Virtual destructor for proper cleanup
};

#endif // OBSERVER_H
