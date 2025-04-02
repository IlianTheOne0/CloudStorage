#include "../presenter.h"  
#include "../../../../Infrastructure/Config/domainConfig.h"  
#include "../../UseCases/DirectoryUseCase/directoryUseCase.h"  

ViewModel Presenter::CommandHandler::delCommand(vector<wstring> tokens, const bool& consoleShowHidden)
{  
   if (tokens.size() < 2) { return { HeaderTypes::ErrorType, L"Usage: del <name>" }; };  
  
   shared_ptr<Directory> root = Screen::Updater::getData();  
   vector<shared_ptr<Unit>>::iterator it = Tools::find(root, Tools::wstringToString(tokens[1]));

   if (it == root->getContents().end()) { return { HeaderTypes::ErrorType, tokens[1] + L" not found" }; }  

   shared_ptr<Unit> unit = *it;

   if (!consoleShowHidden && unit->getIsHidden()) { return { HeaderTypes::ErrorType, tokens[1] + L" not found" }; }  

   DirectoryUseCase::remove(root, Tools::wstringToString(tokens[1]));
   return { HeaderTypes::SuccessfulType, tokens[1] + L" deleted" };  
}