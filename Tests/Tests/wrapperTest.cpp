#include "../testHandler.h"

#include "../../Libs/testConfig.h"
#include "../../Core/core.h"

class TempEntity
{
public:
	TempEntity() = default;
	~TempEntity() = default;

	string helloMessage() { return "Hello world!"; }
	long long add(long long a, long long b) { return a + b; }
};

void TestHandler::wrapperTest()
{
	Wrapper<TempEntity> obj;

	cout << obj->helloMessage() << endl;
	cout << obj->add(10, 15) << endl;
}