#ifndef SERVICES_ENCRYPTION_ABSTRACTION_H
#define SERVICES_ENCRYPTION_ABSTRACTION_H

#include "IEncryption.h"
#include "../../Logger/logger.h"

#define ERROR(message) Logger::log(message, Error)

#define ITERATIONS 3
#define SALT_SIZE 8
#define KEY_SIZE 16

class AEncryption abstract
    : public IEncryption
{
protected:
    AEncryption() = default;
    ~AEncryption() override = default;

    static vector<unsigned char> generateSalt();
    static vector<unsigned char> deriveKey(const string& password, const vector<unsigned char>& salt);
    static void transpose(vector<unsigned char>& data, const vector<unsigned char>& key);
    static void reverseTranspose(vector<unsigned char>& data, const vector<unsigned char>& key);
};

#endif