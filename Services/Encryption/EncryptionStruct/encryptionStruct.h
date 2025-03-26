#ifndef SERVICES_ENCRYPTION_STRUCT_DATA_H
#define SERVICES_ENCRYPTION_STRUCT_DATA_H

#include "../../../Infrastructure/Config/servicesConfig.h"

struct EncryptionData
{
private:
    unsigned char _SBox[256];
    unsigned char _inverseSBox[256];
    string _data;
public:
    EncryptionData() = default;
    EncryptionData(const unsigned char SBox[256], const unsigned char inverseSBox[256], const string& data);
    EncryptionData(const EncryptionData& other);
    EncryptionData& operator=(const EncryptionData& other);
    ~EncryptionData() = default;

    const unsigned char* getSBox() const;
    const unsigned char* getInverseSBox() const;
    const string& getData() const;
};


#endif