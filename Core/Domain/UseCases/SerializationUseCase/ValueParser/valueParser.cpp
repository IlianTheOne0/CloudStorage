#include "valueParser.h"

template<typename TValue> TValue Parser::parseValue(const string& str)
{
	stringstream stream(str);
	TValue value;
	stream >> value;

	return value;
}

template<>
bool Parser::parseValue<bool>(const string& str)
{
	if (str == "true") return true;
	if (str == "false") return false;

	return static_cast<bool>(stoi(str));
}

time_t Parser::parseTime(const string& str) { return static_cast<time_t>(stol(str)); }

string Parser::parseKey()
{
	skipWhitespace();

	size_t start = pos;
	while (pos < data.size() && data[pos] != ':') { pos++; }
	
	return data.substr(start, pos++ - start);
}

string Parser::parseString()
{
	skipWhitespace();
	if (data[pos++] != '"') { ERROR("class Parser -> method parseString: expected '\"'"); throw runtime_error("expected '\"'"); }

	string result;
	bool escape = false;
	while (pos < data.size())
	{
		if (escape) { escape = false; result += data[pos++]; }
		else if (data[pos] == '\\') { escape = true; pos++; }
		else if (data[pos] == '"') { pos++; return result; }
		else { result += data[pos++]; }
	}
	
	ERROR("class Parser -> method parseString: expected '\"' at pos " + to_string(pos));
	throw runtime_error("Unclosed string");
}

string Parser::parsePrimitive() {
	skipWhitespace();
	if (pos >= data.size()) { ERROR("class Parser -> method parsePrimitive: Unexpected end of data in parsePrimitive at pos " + to_string(pos)); throw runtime_error("Unexpected end of data"); }

	size_t start = pos;
	while (pos < data.size() && data[pos] != ';' && data[pos] != ',' && data[pos] != '}') { pos++; }

	return data.substr(start, pos - start);
}

void Parser::parseContents(vector<shared_ptr<Unit>>& contents)
{
	if (pos >= data.size() || data[pos++] != '[') { ERROR("Expected '[' at pos " + to_string(pos)); throw runtime_error("Expected '['"); }

	while (pos < data.size())
	{
		if (data[pos] == ']') { pos++; return; }
		if (data[pos] == ',') { pos++; }

		contents.push_back(parse());
	}

	ERROR("class Parser -> method parseContents: Unclosed contents array at pos " + to_string(pos)); throw runtime_error("Unclosed contents array");
}

shared_ptr<Directory> Parser::parseDirectory()
{
	shared_ptr<Directory> directory = make_shared<Directory>("", false);

	while (pos < data.size())
	{
		if (data[pos] == '}') { break; }

		string key = parseKey();
		bool isContents = false;

		if (key == "name") { directory->setName(parseString()); }
		else if (key == "isHidden") { string value = parsePrimitive(); directory->setIsHidden(parseValue<bool>(value)); }
		else if (key == "createdDate") { string value = parsePrimitive(); directory->setCreatedDate(parseTime(value)); }
		else if (key == "lastEditedDate") { string value = parsePrimitive(); directory->setLastEditedDate(parseTime(value)); }
		else if (key == "fileType") { string value = parsePrimitive(); directory->setFileType(static_cast<FileTypes>(parseValue<int>(value))); }
		else if (key == "contents") { parseContents(directory->getContents()); isContents = true; }
		else { ERROR("class Parser -> method parseDirectory: unknown key: " + key + " at pos " + to_string(pos)); throw runtime_error("Unknown key: " + key + " at pos " + to_string(pos)); }

		if (!isContents)
		{
			if (pos >= data.size() || data[pos++] != ';')
			{
				ERROR("class Parser -> method parseDirectory: Expected ';' at pos " + to_string(pos));
				throw runtime_error("Expected ';' at pos " + to_string(pos));
			}
		}
	}

	return directory;
}

shared_ptr<AFile> Parser::parseAFile()
{
	string name, content;
	bool isHidden = false;
	time_t createdDate{ 0 }, lastEditedDate{ 0 };
	FileTypes fileType = FileTypes::TextFileType;
	
	while (pos < data.size())
	{
		if (data[pos] == '}') { break; }

		string key = parseKey();
		if (key == "name") { name = parseString(); }
		else if (key == "isHidden") { string value = parsePrimitive(); isHidden = parseValue<bool>(value); }
		else if (key == "createdDate") { string value = parsePrimitive(); createdDate = parseTime(value); }
		else if (key == "lastEditedDate") { string value = parsePrimitive(); lastEditedDate = parseTime(value); }
		else if (key == "fileType") { string value = parsePrimitive(); fileType = static_cast<FileTypes>(parseValue<int>(value)); }
		else if (key == "data") { content = parseString(); }
		else { ERROR("class Parser -> method parseAFile: unknown key: " + key); throw runtime_error("Unknown key: " + key); }

		if (data[pos++] != ';') { ERROR("class Parser -> method parseAFile: Expected ';'"); throw runtime_error("Expected ';'"); }
	}

    shared_ptr<TextFile> file = make_shared<TextFile>(name, content, isHidden);
	file->setCreatedDate(createdDate);
	file->setLastEditedDate(lastEditedDate);

	return file;
}

void Parser::skipWhitespace() { while (pos < data.size() && isspace(data[pos])) { pos++; } }

Parser::Parser(const string& str)
	: data(str)
{ }

shared_ptr<Unit> Parser::parse()
{
	skipWhitespace();

	size_t typeEnd = data.find(':', pos);
	string type = data.substr(pos, typeEnd - pos);
	pos = typeEnd + 2;

	shared_ptr<Unit> result;
	if (type == "Directory") { result = parseDirectory(); }
	else if (type == "AFile") { result = parseAFile(); }
	else { ERROR("class Parser -> method parse: Unknown type: " + type); throw runtime_error("Unknown type: " + type); }

	if (data[pos++] != '}') { ERROR("class Parser -> method parse: Expected '}'"); throw runtime_error("Expected '}'"); }
	return result;
}