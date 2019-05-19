#include "MainApp.h"

int main()
{
	MainApp* app = new MainApp();
	app->Run();
	delete app;
	return 0;
}