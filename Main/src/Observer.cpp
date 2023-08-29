struct Entity 
{
  /* data */
};

struct Event
{
  /* data */
};


class Observer
{
public:
  virtual ~Observer() {}
  virtual void onNotify(const Entity& entity, Event event) = 0;
};