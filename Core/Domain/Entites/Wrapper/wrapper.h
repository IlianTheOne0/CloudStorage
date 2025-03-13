#ifndef WRAPPER_H
#define WRAPPER_H

#include "../../../../Infrastructure/Config/domainConfig.h"

template<typename TValue>
class Wrapper
{
private:
	shared_ptr<TValue> _obj;

	class Proxy
	{
	private:
		TValue* _ptr;
	public:
		Proxy(TValue* ptr)
			: _ptr(ptr)
		{ }
		Proxy() = delete;

		template<typename TMethod, typename... TArgs>
		auto operator()(TMethod method, const string& methodName, TArgs&&... args)
		{
			INFO(string(typeid(TValue).name()) + " -> method " + methodName + ": called;");
			return (_ptr->*method)(forward<TArgs>(args)...);
		}
	};
public:
	template<typename... TArgs> Wrapper(TArgs&&... args)
		: _obj(shared_ptr<TValue>(forward<TArgs>(args)...))
	{ CREATE_INFO(string(typeid(TValue).name()) + " <- constructor: called;"); }
	~Wrapper() { CREATE_INFO(string(typeid(TValue).name()) + " <- destructor: called;"); }

	Proxy call() { return Proxy(_obj.get()); }
};

#endif