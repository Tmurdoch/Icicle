#include <stddef.h>

class Root
{
    private:

    // member variables

    static Root* instancePtr;

    Root() {}

    public:

    Root(const Root& obj) = delete; //delete copy constructor

    static Root* getInstance()
    {
        if (instancePtr == NULL)
        {
            instancePtr = new Root();
            return instancePtr;
        }
    }
    //singletons
}