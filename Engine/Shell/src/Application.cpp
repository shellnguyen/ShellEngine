#include "Application.h"
#include <stdio.h>

namespace shell 
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (true)
		{
			printf("App is running");
		}
	}
}