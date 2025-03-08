#ifndef OBSERVER_H
#define OBSERVER_H

/**
 * @brief The Observer interface that any observer class should implement.
 *
 * This interface defines a method for receiving updates from observed subjects.
 */
class Observer {
public:
    /**
     * @brief Default virtual destructor.
     */
    virtual ~Observer() = default;

    /**
     * @brief Update method called when an observed subject changes.
     */
    virtual void update() = 0;
};

#endif // OBSERVER_H
