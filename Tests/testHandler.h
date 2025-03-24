#ifndef TEST_HANDLER_H
#define TEST_HANDLER_H

class TestHandler
{
private:
    static unsigned short _testCounter;

    static void wrapperTest();
    static void unitTest();
    static void directoryTest();
    static void fileTest();
    static void providersTest();
    //static void totalTestOfAllUnits();
public:
    static void setTestCounter(const unsigned short& value) { _testCounter = value; }
    static void startTheTest()
    {
        switch (_testCounter)
        {
            case 0: { wrapperTest(); } break;
            case 1: { unitTest(); } break;
            case 2: { directoryTest(); } break;
            case 3: { fileTest(); } break;
            case 4: { providersTest(); } break;
            //case 4: { totalTestOfAllUnits(); } break;
            default: {}
        }
    }
};

#endif