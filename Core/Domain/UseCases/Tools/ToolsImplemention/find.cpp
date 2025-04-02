#include "../tools.h"
#include "../../../../../Infrastructure/Config/domainConfig.h"

vector<shared_ptr<Unit>>::iterator Tools::find(const shared_ptr<Directory>& root, const string& targetName)
{
	return find_if(root->getContents().begin(), root->getContents().end(), [&](shared_ptr<Unit>& unit) { return unit->getName() == targetName; });
}