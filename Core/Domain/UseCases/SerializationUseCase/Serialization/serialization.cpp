#include "serialization.h"

string Serializer::serializeString(const string& str)
{
	string result;

	for (char ch : str) { if (ch == '\"' || ch == '\\') { result += '\\'; } result += ch; }

	return result;
}

string Serializer::serializeUnit(const Unit* unit)
{
	stringstream stream;
	stream
		<< "name:\"" << serializeString(unit->getName()) << "\";"
		<< "isHidden:" << (unit->getIsHidden() ? "true" : "false") << ";"
		<< "createdDate:" << unit->getCreatedDate() << ";"
		<< "lastEditedDate:" << unit->getLastEditedDate() << ";"
		<< "fileType:" << static_cast<int>(unit->getFileType()) << ";";

	return stream.str();
}

string Serializer::serializeAFile(const AFile* file) {
	stringstream stream;
	stream
		<< "AFile:{"
		<< serializeUnit(static_cast<const Unit*>(file))
		<< "data:\"" << serializeString(file->getContent()) << "\";}";

	return stream.str();
}

string Serializer::serializeDirectory(const Directory* directory)
{
	stringstream stream;
	stream
		<< "Directory:{"
		<< serializeUnit(static_cast<const Unit*>(directory))
		<< "contents:[";

	const auto& contents = directory->getContents();
	for (size_t i = 0; i < contents.size(); ++i) {
		if (i > 0) stream << ",";

		if (auto dir = dynamic_cast<const Directory*>(contents[i].get())) { stream << serializeDirectory(dir); }
		else if (auto file = dynamic_cast<const AFile*>(contents[i].get())) { stream << serializeAFile(file); }
	}

	stream << "]}";

	return stream.str();
}

shared_ptr<Unit> Serializer::deserialize(const string& data) { return Parser(data).parse(); }