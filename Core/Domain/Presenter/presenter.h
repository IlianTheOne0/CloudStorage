#ifndef PRESENTER_H
#define PRESENTER_H

#include "IPresenter.h"
#include "../../Presentation/presentation.h"

class Presenter
	: public IPresenter
{
private:
	class CommandHandler
	{
	public:
		static ViewModel cdCommand(vector<wstring> tokens, const bool& consoleShowHidden);
		static ViewModel changeCommand(vector<wstring> tokens, const bool& consoleShowHidden, ConfigParser& config);
		static ViewModel delCommand(vector<wstring> tokens, const bool& consoleShowHidden);
		static ViewModel exitCommand(vector<wstring> tokens);
		static ViewModel infoCommand(vector<wstring> tokens, const bool& consoleShowHidden);
		static ViewModel mkdirCommand(vector<wstring> tokens);
		static ViewModel notepadCommand(vector<wstring> tokens);
		static ViewModel openCommand(vector<wstring> tokens, const bool& consoleShowHidden);
		static ViewModel renameCommand(vector<wstring> tokens, const bool& consoleShowHidden);
		static ViewModel updateCommand(vector<wstring> tokens);
	};
public:
	Presenter() = default;
	~Presenter() override = default;

	ViewModel handle(const wstring& input) override;
};

#endif