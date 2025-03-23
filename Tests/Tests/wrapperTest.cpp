#include "../testHandler.h"

#include "../../Infrastructure/Config/testConfig.h"
#include "../../Core/core.h"

class Entity
{
public:
    Entity() = default;
    ~Entity() = default;

    string helloMessage() { return "Hello world!"; }
    long long add(long long a, long long b) { return a + b; }
    static string staticHelloMessage() { return "Static Hello world!"; }
    static long long staticAdd(long long a, long long b) { return a + b; }
};

void TestHandler::wrapperTest()
{
    Wrapper<Entity> obj;

    cout << obj.call()(&Entity::helloMessage, "helloMessage") << endl;
    cout << obj.call()(&Entity::add, "add", 10, 5) << endl;

    cout << StaticWrapper<Entity>::call()(&Entity::staticHelloMessage, "staticHelloMessage") << endl;
    cout << StaticWrapper<Entity>::call()(&Entity::staticAdd, "staticAdd", 10, 5) << endl;
}