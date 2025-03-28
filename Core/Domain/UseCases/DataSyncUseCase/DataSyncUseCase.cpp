#include "DataSyncUseCase.h"
#include "../../../Data/data.h"
#include "../../../../Services/services.h"

bool DataSyncUseCase::synkFromRemote()
{
	try {
		LocalProvider local;
		RemoteProvider remote;

		local.save(remote.load());
	}
	catch (const exception& e) { throw e; }

	return true;
}

bool DataSyncUseCase::synkFromLocal()
{
	try {
		LocalProvider local;
		RemoteProvider remote;

		remote.save(local.load());
	}
	catch (const exception& e) { throw e; }

	return true;
}

bool DataSyncUseCase::setData(const string& serialized) {
    try {
        string password = KeyRandomizer::generateRandomKey();
        Encryptor encryptor;
        EncryptionData encryptedData = encryptor.encrypt(serialized, password);

        const unsigned char* sbox = encryptedData.getSBox();
        const unsigned char* invertedSBox = encryptedData.getInverseSBox();
        string encryptedDataStr = encryptedData.getData();

        stringstream stream;
        stream.write(reinterpret_cast<const char*>(sbox), 256);
        stream.write(reinterpret_cast<const char*>(invertedSBox), 256);
        stream.write(password.data(), password.size());
        stream.write(encryptedDataStr.data(), encryptedDataStr.size());

        LocalProvider local;
        local.save(stream.str());
    }
    catch (const exception& e) { throw e; }
    return true;
}

string DataSyncUseCase::getData() {
    LocalProvider local;
    string decryptedData;

    try {
        string data = local.load();

        if (data.size() < 256 * 2 + 512) { ERROR("class DataSyncUseCase -> static method synkFromRemote: invalid line length! (" + to_string(data.size()) + ");"); throw invalid_argument("invalid line length! (" + to_string(data.size()) + ")"); }

        size_t pos = 0; string sbox_part = data.substr(pos, 256);
        pos += 256; string invertedSBox_part = data.substr(pos, 256);
        pos += 256; string password_part = data.substr(pos, 512);
        pos += 512; string encryptedData_part = data.substr(pos);

        unsigned char sboxArray[256], invertedSBoxArray[256];
        memcpy(sboxArray, sbox_part.data(), 256);
        memcpy(invertedSBoxArray, invertedSBox_part.data(), 256);

        Decryptor decryptor;
        decryptedData = decryptor.decrypt(EncryptionData(sboxArray, invertedSBoxArray, encryptedData_part), password_part);
    }
    catch (const exception& e) { throw e; }

    return decryptedData;
}