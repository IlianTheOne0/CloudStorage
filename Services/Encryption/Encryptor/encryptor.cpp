#include "encryptor.h"

EncryptionData Encryptor::encrypt(const string& data, const string& password)
{
    vector<unsigned char> plain(data.begin(), data.end());
    if (plain.empty()) return EncryptionData();

    vector<unsigned char> salt = generateSalt();
    vector<unsigned char> key = deriveKey(password, salt);
    auto sboxPair = ByteRandomizer::generateSBox();
    auto sbox = sboxPair.first;
    auto inverse_sbox = sboxPair.second;

    for (int round = 0; round < ITERATIONS; round++)
    {
        for (size_t i = 0; i < plain.size(); i++) { plain[i] ^= key[(i + round) % key.size()]; }
        for (unsigned char& byte : plain) { byte = sbox[byte]; }

        transpose(plain, key);
    }

    plain.insert(plain.begin(), salt.begin(), salt.end());

    string encryptedData(plain.begin(), plain.end());
    return EncryptionData(sbox.data(), inverse_sbox.data(), encryptedData);
}

string Encryptor::decrypt(const EncryptionData& encryptionData, const string& password) { ERROR("class Encryptor -> method decrypt: This class is for encryption only!"); throw domain_error("This class is for encryption only!"); }