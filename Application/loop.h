#ifndef APPLICATION_LOOP_H
#define APPLICATION_LOOP_H

#include "../Core/core.h"

wstring toWString2(const string& str)
{
    size_t size;
    mbstowcs_s(&size, nullptr, 0, str.c_str(), 0);
    vector<wchar_t> buffer(size);
    mbstowcs_s(&size, buffer.data(), size, str.c_str(), size - 1);

    return wstring(buffer.data());
}

void loop()
{
    try
    {
        ConsoleView view;
        Presenter presenter;
        view.setTerminalProperties();

        DataSyncUseCase::synkFromRemote();
        string serializedData = DataSyncUseCase::getData();

        shared_ptr<Directory> rootDirectory = nullptr;
        if (!serializedData.empty())
        {
            //wcout << toWString2(serializedData) << endl; system("pause");
            shared_ptr<Unit> rootUnit = Serializer::deserialize(serializedData);
            rootDirectory = dynamic_pointer_cast<Directory>(rootUnit);
        }
        else { rootDirectory = make_shared<Directory>("root", false); }

        if (!rootDirectory) { throw runtime_error("Failed to load directory structure"); }

        Screen::Updater::setData(rootDirectory);
        Screen::Updater::start(presenter);

        while (!Screen::Updater::getExitFlag()) { Screen::Updater::update(); }

        string finalData = Serializer::serializeDirectory(rootDirectory.get());
        //wcout << toWString2(finalData) << endl; system("pause");
        DataSyncUseCase::setData(finalData);
        DataSyncUseCase::synkFromLocal();

    }
    catch (const exception& e) { cerr << "Exception: " << e.what() << endl; }
    catch (...) { cerr << "Unknown exception occurred!" << endl; }
    
    wcout << "Now you can close the app!" << endl;
}

#endif