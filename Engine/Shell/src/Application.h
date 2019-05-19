#ifndef APPLICATION_H
#define APPLICATION_H

#include "Utils\Common.h"

namespace shell 
{
	class SHELL_API Application
	{
	private:
	public:
		Application();
		virtual ~Application();

		virtual void Run();
	};
}

#endif // !APPLICATION_H

