#ifndef SERVICES_ENCRYPTION_ENCRYPTOR_H
#define SERVICES_ENCRYPTION_ENCRYPTOR_H

#include "../Base/AEncryption.h"
#include "../../Randomizers/randomizers.h"

class Encryptor
	: public AEncryption
{
public:
	Encryptor() = default;
	~Encryptor() override = default;

	EncryptionData encrypt(const string& data, const string& password) override;
	string decrypt(const EncryptionData& encryptionData, const string& password) override;
};

#endif