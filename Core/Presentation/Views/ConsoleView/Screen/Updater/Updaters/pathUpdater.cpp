#include "../../screen.h"
#include "../../../consoleView.h"

using namespace Screen;

void Updater::updatePath()
{
    if (_rootDirectory)
    {
        const auto& directoryName = _rootDirectory->getName();
        wstring currentDirName(directoryName.begin(), directoryName.end());

        vector<wstring> pathElements;
        wstringstream stream(_path);
        wstring item;

        while (getline(stream, item, L'\\')) { if (!item.empty()) { pathElements.push_back(item); } }

        if (!pathElements.empty() && pathElements.back() == currentDirName) { return; }
        else if (pathElements.size() > 1 && pathElements[pathElements.size() - 2] == currentDirName) { pathElements.pop_back(); }
        else { pathElements.push_back(currentDirName); }

        wstring newPath;
        for (const wstring& elem : pathElements) { newPath += elem + L'\\'; }

        _path = newPath;
    }
}