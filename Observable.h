#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <vector>
#include <algorithm>
#include "Observer.h"

/**
 * @brief The Observable interface that any subject class should implement.
 *
 * This interface provides methods for attaching, detaching, and notifying observers.
 */
class Observable {
private:
    std::vector<Observer*> observers;

public:
    /**
     * @brief Default virtual destructor.
     */
    virtual ~Observable() = default;

    /**
     * @brief Attach an observer to this observable object.
     *
     * @param observer The observer to attach.
     */
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    /**
     * @brief Detach an observer from this observable object.
     *
     * @param observer The observer to detach.
     */
    void detach(Observer* observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
            );
    }

    /**
     * @brief Notify all observers that this observable object has changed.
     */
    void notify() {
        for (Observer* observer : observers) {
            observer->update();
        }
    }
};

#endif // OBSERVABLE_H
