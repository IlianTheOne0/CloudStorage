#ifndef SERVICES_ENCRYPTION_DECRYPTOR_H
#define SERVICES_ENCRYPTION_DECRYPTOR_H

#include "../Base/AEncryption.h"

class Decryptor
	: public AEncryption
{
public:
	Decryptor() = default;
	~Decryptor() override = default;

	EncryptionData encrypt(const string& data, const string& password) override;
	string decrypt(const EncryptionData& encryptionData, const string& password) override;
};

#endif