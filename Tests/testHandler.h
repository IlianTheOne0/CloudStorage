#ifndef TEST_HANDLER_H
#define TEST_HANDLER_H

class TestHandler
{
private:
    static unsigned short _testCounter;

    static void wrapperTest();
public:
    static void setTestCounter(const unsigned short& value) { _testCounter = value; }
    static void startTheTest()
    {
        switch (_testCounter)
        {
        case 0: { wrapperTest(); } break;
        default: {}
        }
    }
};

#endif