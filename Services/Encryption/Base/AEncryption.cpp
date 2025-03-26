#include "AEncryption.h"

vector<unsigned char> AEncryption::generateSalt()
{
    vector<unsigned char> salt(SALT_SIZE);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 255);

    generate(salt.begin(), salt.end(), [&]() { return static_cast<unsigned char>(dis(gen)); });

    return salt;
}

vector<unsigned char> AEncryption::deriveKey(const string& password, const vector<unsigned char>& salt)
{
    vector<unsigned char> key(KEY_SIZE);
    
    for (size_t i = 0; i < KEY_SIZE; ++i) { key[i] = password[i % password.size()] ^ salt[i % salt.size()]; }
    return key;
}

void AEncryption::transpose(vector<unsigned char>& data, const vector<unsigned char>& key)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        size_t new_pos = (i + key[i % key.size()]) % data.size();
        swap(data[i], data[new_pos]);
    }
}

void AEncryption::reverseTranspose(vector<unsigned char>& data, const vector<unsigned char>& key)
{
    for (size_t i = data.size(); i > 0; i--)
    {
        size_t pos = i - 1;
        size_t new_pos = (pos + key[pos % key.size()]) % data.size();
        swap(data[pos], data[new_pos]);
    }
}