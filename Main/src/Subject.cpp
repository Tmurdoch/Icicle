#include "Observer.cpp"

#define MAX_OBSERVERS 10

class Subject
{
private:
  Observer* observers_[MAX_OBSERVERS];
  int numObservers_;

public:

void addObserver(Observer* observer)
  {
    // Add to array...
  }

void removeObserver(Observer* observer)
  {
    // Remove from array...
  }

  // Other stuff...

protected:
void notify(const Entity& entity, Event event)
  {
    for (int i = 0; i < numObservers_; i++)
    {
      observers_[i]->onNotify(entity, event);
    }
  }  

};