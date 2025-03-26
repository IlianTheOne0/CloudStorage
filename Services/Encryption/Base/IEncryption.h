#ifndef SERVICES_ENCRYPTION_INTERFACE_H
#define SERVICES_ENCRYPTION_INTERFACE_H

#include "../../../Infrastructure/Config/servicesConfig.h"
#include "../EncryptionStruct/encryptionStruct.h"

class IEncryption
{
public:
	virtual ~IEncryption() = default;

	virtual EncryptionData encrypt(const string& data, const string& password) = 0;
	virtual string decrypt(const EncryptionData& encryptionData, const string& password) = 0;
};

#endif