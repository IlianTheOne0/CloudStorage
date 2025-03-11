#ifndef WRAPPER_H
#define WRAPPER_H

#include "../../../../Utils/domainConfig.h"

template<typename TValue>
class Wrapper
{
private:
	shared_ptr<TValue> _obj;
public:
	template<typename... TArgs> Wrapper(TArgs&&... args)
		: _obj(shared_ptr<TValue>(forward<TArgs>(args)...))
	{ CREATE_INFO("Wrapper <- constructor: An object of the class was created: " + string(typeid(TValue).name()) + ";"); }
	~Wrapper() { CREATE_INFO("Wrapper <- destructor: An object of the class was deleted: " + string(typeid(TValue).name()) + ";"); }

	TValue* operator->()
	{
		INFO("Wrapper -> " + string(typeid(TValue).name()) + ": method called;");
		return _obj.get();
	}
};

#endif