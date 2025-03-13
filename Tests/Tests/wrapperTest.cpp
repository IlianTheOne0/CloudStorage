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
};

void TestHandler::wrapperTest()
{
	Wrapper<Entity> obj;

	cout << obj.call()(&Entity::helloMessage, "helloMessage") << endl;
	cout << obj.call()(&Entity::add, "add", 10, 5) << endl;
}