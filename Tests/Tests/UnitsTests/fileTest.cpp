#include "../../testHandler.h"
#include "../../../Infrastructure/Config/testConfig.h"
#include "../../../Core/Domain/Entites/File/file.h"
#include "../../../Core/Domain/UseCases/TextFileUseCase/textFileUseCase.h"

void testConstructorAndGetContent()
{
    string name = "testFile";
    string content = "This is a test content.";
    bool isHidden = false;

    Wrapper<TextFile> textFile(name, content, isHidden);
    textFile = Wrapper<TextFile>(name, content, isHidden);

    cout << "Name: " << textFile.call()(&TextFile::getName, "getName") << endl;
    cout << "Content: " << textFile.call()(&TextFile::getContent, "getContent") << endl;
    cout << "Is Hidden: " << textFile.call()(&TextFile::getIsHidden, "getIsHidden") << endl;

    if (textFile.call()(&TextFile::getName, "getName") == name && textFile.call()(&TextFile::getContent, "getContent") == content && textFile.call()(&TextFile::getIsHidden, "getIsHidden") == isHidden) { cout << "Test case 1 passed: Constructor and getContent" << endl; }
    else { cout << "Test case 1 failed: Constructor and getContent" << endl; }
}

void testEditContentAndGetContent()
{
    string name = "testFile";
    string initialContent = "Initial content.";
    string newContent = "Updated content.";
    bool isHidden = false;

    Wrapper<TextFile> textFile(name, initialContent, isHidden);
    textFile.call()(&TextFile::editContent, "editContent", newContent);
    textFile = Wrapper<TextFile>(name, newContent, isHidden);

    cout << "Name: " << textFile.call()(&TextFile::getName, "getName") << endl;
    cout << "Content: " << textFile.call()(&TextFile::getContent, "getContent") << endl;
    cout << "Is Hidden: " << textFile.call()(&TextFile::getIsHidden, "getIsHidden") << endl;

    if (textFile.call()(&TextFile::getContent, "getContent") == newContent) { cout << "Test case 2 passed: editContent and getContent" << endl; }
    else { cout << "Test case 2 failed: editContent and getContent" << endl; }
}

void TestHandler::fileTest()
{
    testConstructorAndGetContent();
    testEditContentAndGetContent();
}