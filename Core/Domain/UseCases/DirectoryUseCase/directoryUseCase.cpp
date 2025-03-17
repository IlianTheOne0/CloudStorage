#include "directoryUseCase.h"

DirectoryUseCase::DirectoryUseCase(const string& name, const bool& isHidden)
    : _directory(new Directory(name, isHidden))
{
    ConfigParser config(CONFIG_PATH);
    if (!config.load()) { cerr << "Error: Cannot load the config" << endl; return; }
    _maxSize = stoi(config.get("directoryMaxSize"));
}
DirectoryUseCase::~DirectoryUseCase() { if (_directory) { delete _directory; } }

void DirectoryUseCase::add(UnitUseCase* item)
{
    if (_directory->_vObjects.size() >= _maxSize) { cerr << "Error: Cannot add item. Directory has reached its maximum size." << endl; return; }
    _directory->_vObjects.push_back(item);
}
void DirectoryUseCase::remove(UnitUseCase* item)
{
    vector<UnitUseCase*>& objects = _directory->_vObjects;

    vector<UnitUseCase*>::iterator iterator = find(objects.begin(), objects.end(), item);
    if (iterator != objects.end()) { objects.erase(iterator); }
}

void DirectoryUseCase::add(const string& name)
{
    if (_directory->_vObjects.size() >= _maxSize) { cerr << "Error: Cannot add item. Directory has reached its maximum size." << endl; return; }

    UnitUseCase* newItem = new UnitUseCase(name);
    add(newItem);
}
void DirectoryUseCase::remove(const string& name)
{
    vector<UnitUseCase*>& objects = _directory->_vObjects;

    vector<UnitUseCase*>::iterator iterator = find_if(objects.begin(), objects.end(), [&name](UnitUseCase* item) { return item->getUnit()->getName() == name; });
    if (iterator != objects.end()) { remove(*iterator); }
}

map<string, string> DirectoryUseCase::getInfo() const
{
    ConfigParser config(CONFIG_PATH);
    if (!config.load()) { cerr << "Error: Cannot load the config" << endl; return map<string, string>(); }
    size_t maxSize = stoi(config.get("directoryMaxSize"));

    map<string, string> info;

    info["name"] = _directory->getUnit()->getName();
    info["isHidden"] = _directory->getUnit()->getIsHidden() ? "true" : "false";

    int numDigits = to_string(maxSize).length();
    
    const vector<UnitUseCase*> objects = _directory->_vObjects;

    for (size_t i = 0; i < objects.size(); ++i) {
        map<string, string> objectInfo = objects[i]->getInfo();

        ostringstream formattedName;
        formattedName << "directory" << setw(numDigits) << setfill('0') << i;

        for (const pair<const string, string>& entry : objectInfo) { info[formattedName.str() + "_" + entry.first] = entry.second; }
    }

    return info;
}