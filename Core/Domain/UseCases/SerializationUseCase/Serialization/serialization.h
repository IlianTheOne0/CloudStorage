#ifndef SERIALIZATION_USECASE_H
#define SERIALIZATION_USECASE_H

#include "../../../Entities/entities.h"
#include "../../../../../Infrastructure/Config/domainConfig.h"
#include "../ValueParser/valueParser.h"

class Serializer
{
public:
	static string serializeString(const string& str);
	static string serializeUnit(const Unit* unit);
	static string serializeAFile(const AFile* file);
	static string serializeDirectory(const Directory* directory);

	static shared_ptr<Unit> deserialize(const string& data);
};

#endif