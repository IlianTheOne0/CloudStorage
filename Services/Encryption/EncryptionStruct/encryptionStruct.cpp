#include "encryptionStruct.h"

EncryptionData::EncryptionData(const unsigned char SBox[256], const unsigned char inverseSBox[256], const string& data)
{
    copy(SBox, SBox + 256, _SBox);
    copy(inverseSBox, inverseSBox + 256, _inverseSBox);
    _data = data;
}

EncryptionData::EncryptionData(const EncryptionData& other)
{
    copy(other._SBox, other._SBox + 256, _SBox);
    copy(other._inverseSBox, other._inverseSBox + 256, _inverseSBox);
    _data = other._data;
}

EncryptionData& EncryptionData::operator=(const EncryptionData& other)
{
    if (this != &other)
    {
        copy(other._SBox, other._SBox + 256, _SBox);
        copy(other._inverseSBox, other._inverseSBox + 256, _inverseSBox);
        _data = other._data;
    }
    return *this;
}

const unsigned char* EncryptionData::getSBox() const { return _SBox; }
const unsigned char* EncryptionData::getInverseSBox() const { return _inverseSBox; }
const string& EncryptionData::getData() const { return _data; }