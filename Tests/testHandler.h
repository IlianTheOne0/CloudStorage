#ifndef TEST_HANDLER_H
#define TEST_HANDLER_H

class TestHandler
{
private:
    static unsigned short _testCounter;

    static void wrapperTest();
    static void unitTest();
    static void directoryTest();
public:
    static void setTestCounter(const unsigned short& value) { _testCounter = value; }
    static void startTheTest()
    {
        switch (_testCounter)
        {
            case 0: { wrapperTest(); } break;
            case 1: { unitTest(); } break;
            case 2: { directoryTest(); } break;
            default: {}
        }
    }
};

#endif