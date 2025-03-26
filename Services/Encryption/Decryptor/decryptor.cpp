#include "decryptor.h"

EncryptionData Decryptor::encrypt(const string& data, const string& password) { ERROR("class Decryptor -> method encrypt: This class is for decryption only!"); throw domain_error("This class is for decryption only!"); }

string Decryptor::decrypt(const EncryptionData& encryptedData, const string& password)
{
    const string& data = encryptedData.getData();
    if (data.size() <= SALT_SIZE) return "";

    vector<unsigned char> salt(data.begin(), data.begin() + SALT_SIZE);
    vector<unsigned char> result(data.begin() + SALT_SIZE, data.end());
    vector<unsigned char> key = deriveKey(password, salt);
    const unsigned char* inverse_sbox = encryptedData.getInverseSBox();

    for (int round = ITERATIONS - 1; round >= 0; round--)
    {
        reverseTranspose(result, key);

        for (unsigned char& byte : result) { byte = inverse_sbox[byte]; }
        for (size_t i = 0; i < result.size(); i++) { result[i] ^= key[(i + round) % key.size()]; }
    }
    
    cout << endl << endl;
    cout << endl << endl;
    cout << endl << endl;
    cout << encryptedData.getSBox() << endl;
    cout << endl << endl;
    cout << encryptedData.getInverseSBox() << endl;
    cout << endl << endl;
    cout << endl << endl;
    cout << endl << endl;

    return string(result.begin(), result.end());
}