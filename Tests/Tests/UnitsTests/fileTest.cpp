#include "../../testHandler.h"
#include "../../../Infrastructure/Config/testConfig.h"
#include "../../../Core/Domain/Entites/File/file.h"
#include "../../../Core/Domain/UseCases/TextFileUseCase/textFileUseCase.h"

void testConstructorAndGetContent()
{
    string name = "testFile";
    string content = "This is a test content.";
    bool isHidden = false;

    AFile* textFile = new TextFile(name, content, isHidden);

    cout << "Name: " << textFile->getName() << endl;
    cout << "Content: " << textFile->getContent() << endl;
    cout << "Is Hidden: " << textFile->getIsHidden() << endl;

    if (textFile->getName() == name && textFile->getContent() == content && textFile->getIsHidden() == isHidden) { cout << "Test case 1 passed: Constructor and getContent" << endl; }
    else { cout << "Test case 1 failed: Constructor and getContent" << endl; }
}

void testEditContentAndGetContent()
{
    string name = "testFile";
    string initialContent = "Initial content.";
    string newContent = "Updated content.";
    bool isHidden = false;

    TextFile textFile(name, initialContent, isHidden);
    textFile.editContent(newContent);

    cout << "Name: " << textFile.getName() << endl;
    cout << "Content: " << textFile.getContent() << endl;
    cout << "Is Hidden: " << textFile.getIsHidden() << endl;

    if (textFile.getContent() == newContent) { cout << "Test case 2 passed: editContent and getContent" << endl; }
    else { cout << "Test case 2 failed: editContent and getContent" << endl; }
}

void TestHandler::fileTest()
{
    testConstructorAndGetContent();
    testEditContentAndGetContent();
}