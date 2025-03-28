#ifndef SERIALIZATION_VALUEPARSER_USECASE_H
#define SERIALIZATION_VALUEPARSER_USECASE_H

#include "../../../Entites/entites.h"
#include "../../TextFileUseCase/textFileUseCase.h"
#include "../../../../../Infrastructure/Config/domainConfig.h"

class Parser
{
private:
	const string& data;
	size_t pos = 0;

	template<typename TValue> TValue parseValue(const string& str);
	time_t parseTime(const string& str);
	void skipWhitespace();
	string parseKey();
	string parseString();

	string parsePrimitive();
	void parseContents(vector<shared_ptr<Unit>>& contents);
	shared_ptr<Directory> parseDirectory();
	shared_ptr<AFile> parseAFile();
public:
	Parser() = default;
	Parser(const string& str);
	virtual ~Parser() = default;

	shared_ptr<Unit> parse();
};

#endif