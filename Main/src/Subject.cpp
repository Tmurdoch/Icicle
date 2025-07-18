#include "Subject.hpp"
#include <vector>
#include <algorithm>

namespace Icicle {
  
#define MAX_OBSERVERS 10

// Template-based Subject
    template<typename T>
    void Subject<T>::subscribe(Observer<T>* observer) {
        observers.push_back(observer);
    }

    template<typename T>
    void Subject<T>::unsubscribe(Observer<T>* observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    template<typename T>
    void Subject<T>::notify(const T& data) {
        for (auto* observer : observers) {
            observer->update(data);
        }
    }
};

