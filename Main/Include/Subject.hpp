#include "Observer.hpp"
#include <vector>
#include <algorithm>

namespace Icicle {
  
#define MAX_OBSERVERS 10

// Template-based Subject
template<typename T>
class Subject {
private:
    std::vector<Observer<T>*> observers;
    
public:
    virtual ~Subject() = default;
    
    void subscribe(Observer<T>* observer); 
    
    void unsubscribe(Observer<T>* observer);     

protected:
    void notify(const T& data);

};
}
