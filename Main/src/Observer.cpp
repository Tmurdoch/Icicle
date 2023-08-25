typedef struct Entity 
{
  /* data */
};

typedef struct Event
{
  /* data */
};


class Observer
{
public:
  virtual ~Observer() {}
  virtual void onNotify(const Entity& entity, Event event) = 0;
};