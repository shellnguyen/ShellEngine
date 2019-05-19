#ifndef MAIN_APP_H
#define MAIN_APP_H

#include "Shell.h"

class MainApp : public shell::Application
{
public:
	MainApp();
	virtual ~MainApp();
	void Run() override;
};

#endif // !MAIN_APP_H

