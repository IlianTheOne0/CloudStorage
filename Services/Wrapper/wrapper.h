#ifndef WRAPPER_H
#define WRAPPER_H

#include "../../Infrastructure/Config/servicesConfig.h"
#include "../Logger/logger.h"

#define CREATE_INFO(message) Logger::log(message, InfoADD)
#define INFO(message) Logger::log(message, Info)

template<typename TValue>
class Wrapper
{
private:
    shared_ptr<TValue> _obj;

    class WrapperPtr
    {
    private:
        shared_ptr<TValue> _ptr;
    public:
        WrapperPtr(shared_ptr<TValue> ptr)
            : _ptr(ptr)
        { }

        WrapperPtr() = delete;

        template<typename TMethod, typename... TArgs>
        auto operator()(TMethod method, const string& methodName, TArgs&&... args)
        {
            INFO(string(typeid(TValue).name()) + " -> method " + methodName + ": called;");
            return (_ptr.get()->*method)(forward<TArgs>(args)...);
        }
    };

public:
    template<typename... TArgs> Wrapper(TArgs&&... args)
        : _obj(make_shared<TValue>(forward<TArgs>(args)...))
    { CREATE_INFO(string(typeid(TValue).name()) + " <- constructor: called;"); }

    ~Wrapper() { CREATE_INFO(string(typeid(TValue).name()) + " <- destructor: called;"); }

    WrapperPtr call() { return WrapperPtr(_obj); }
    shared_ptr<TValue> get() { return _obj; }
};

template<typename TValue>
class StaticWrapper
{
public:
    class StaticWrapperPtr
    {
    public:
        StaticWrapperPtr() = default;

        template<typename TMethod, typename... TArgs>
        auto operator()(TMethod method, const string& methodName, TArgs&&... args)
        {
            INFO(string(typeid(TValue).name()) + " -> static method " + methodName + ": called;");
            return method(forward<TArgs>(args)...);
        }
    };

    static StaticWrapperPtr call() { return StaticWrapperPtr(); }
};

#endif