#ifndef STATIC_WRAPPER_H
#define STATIC_WRAPPER_H

#include "../../Infrastructure/Config/servicesConfig.h"
#include "../Logger/logger.h"

#define CREATE_INFO(message) Logger::log(message, InfoADD)
#define INFO(message) Logger::log(message, Info)

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