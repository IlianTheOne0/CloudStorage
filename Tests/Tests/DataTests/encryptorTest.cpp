#include "../../testHandler.h"
#include "../../../Infrastructure/Config/testConfig.h"

void testNewEncryptor(const string& data, const string& password)
{
    Wrapper<Encryptor> encryptor;

    try
    {
        EncryptionData encrypted = encryptor.call()(&Encryptor::encrypt, "encrypt", data, password);
        cout << "Encrypted: " << encrypted.getData() << endl;
    }
    catch (const exception& e) { cout << "Encryption failed: " << e.what() << endl; }
}

void testNewDecryptor(const EncryptionData& encryptedData, const string& password)
{
    Wrapper<Decryptor> decryptor;

    try
    {
        string decrypted = decryptor.call()(&Decryptor::decrypt, "decrypt", encryptedData, password);
        cout << "Decrypted: " << decrypted << endl;
    }
    catch (const exception& e) { cout << "Decryption failed: " << e.what() << endl; }
}

void testNewEncryptorDecryptCall(const EncryptionData& encryptedData, const string& password)
{
    Wrapper<Encryptor> encryptor;

    try
    {
        string decrypted = encryptor.call()(&Encryptor::decrypt, "decrypt", encryptedData, password);
        cout << "Unexpected success: " << decrypted << endl;
    }
    catch (const exception& e) { cout << "Expected exception: " << e.what() << endl; }
}

void testNewDecryptorEncryptCall(const string& data, const string& password)
{
    Wrapper<Decryptor> decryptor;

    try
    {
        EncryptionData encrypted = decryptor.call()(&Decryptor::encrypt, "encrypt", data, password);
        cout << "Unexpected success: " << encrypted.getData() << endl;
    }
    catch (const exception& e) { cout << "Expected exception: " << e.what() << endl; }
}

void TestHandler::encryptorTest()
{
    string data = "Hello, World!";
    string password = "password123";

    Wrapper<Encryptor> encryptor;
    EncryptionData encrypted;

    try { encrypted = encryptor.call()(&Encryptor::encrypt, "encrypt", data, password); }
    catch (const exception& e) { cout << "Encryption failed: " << e.what() << endl; return; }

    testNewEncryptor(data, password);
    testNewDecryptor(encrypted, password);
    testNewEncryptorDecryptCall(encrypted, password);
    testNewDecryptorEncryptCall(data, password);
}