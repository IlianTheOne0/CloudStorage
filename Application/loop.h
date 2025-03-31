#ifndef APPLICATION_LOOP_H
#define APPLICATION_LOOP_H

#include "../Core/core.h"

//wstring toWString2(const string& str)
//{
//    size_t size;
//    mbstowcs_s(&size, nullptr, 0, str.c_str(), 0);
//    vector<wchar_t> buffer(size);
//    mbstowcs_s(&size, buffer.data(), size, str.c_str(), size - 1);
//
//    return wstring(buffer.data());
//}

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

        if (!rootDirectory) { ERROR("Loop: Failed to load the directory!;"); throw runtime_error("Failed to load the directory!"); }

        Screen::Updater::setData(rootDirectory);
        Screen::Updater::start(presenter);

        while (!Screen::Updater::getExitFlag()) { Screen::Updater::update(); }

        Screen::Updater updaterInstance;
        rootDirectory = dynamic_pointer_cast<Directory>(updaterInstance.getData());
        string newSerializedData = Serializer::serializeDirectory(rootDirectory.get());
        DataSyncUseCase::setData(newSerializedData);
        DataSyncUseCase::synkFromLocal();
    }
    catch (const exception& e) { ERROR("Loop: " + string(e.what()) + ";"); cerr << "Exception: " << e.what() << endl; }
    catch (...) { ERROR("Loop: Unknown exception occurred;"); cerr << "Unknown exception occurred!" << endl; }
}

#endif
