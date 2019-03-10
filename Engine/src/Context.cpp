#include "Context.h"

Context* Context::m_Instance = NULL;

Context::Context()
{
	m_Window = NULL;
}

Context* Context::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new Context();
	}
	return m_Instance;
}

bool Context::Initialize(int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("SDL Init failed : %d", SDL_GetError());
		return false;
	}

	m_Window = SDL_CreateWindow("GameEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	if (!m_Window)
	{
		SDL_Log("SDL Window Init fail: %d", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	//Opengl part
	m_GlContext = SDL_GL_CreateContext(m_Window);

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		SDL_Log("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		return false;
	}

	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		SDL_Log("Warning: Unable to set Vsync ! Error %d", SDL_GetError());
		return false;
	}

	glViewport(0, 0, width, height);
	return true;
}

void Context::SetFPS(Uint32 fps)
{
	m_FPS = fps;
	m_FrameTime = 1000 / m_FPS;
	m_DeltaTime = m_FrameTime;
}

void Context::GameLoop()
{
	bool isRunning = true;
	SDL_Event e;

	if (m_FnPostInit)
	{
		if (!m_FnPostInit())
		{
			return;
		}
	}

	while (isRunning)
	{
		Uint32 startTime = SDL_GetTicks();

		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				m_FnKeyDown(e.key.keysym.sym);
				break;
			case SDL_KEYUP:
				m_FnKeyUp(e.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_FnMouseDown(e.button.button, e.motion.x, e.motion.y);
				break;
			case SDL_MOUSEMOTION:
				m_FnMouseMotion(e.motion.x, e.motion.y);
				break;
			case SDL_MOUSEWHEEL:
				m_FnMouseWheel(e.wheel.x, e.wheel.y);
				break;
			}
		}

		if (m_FnUpdate != NULL)
		{
			m_FnUpdate(m_DeltaTime / 1000.0f);
		}


		if (m_FnRender != NULL)
		{
			//SDL_RenderClear(gRenderer);
			m_FnRender();
			//SDL_RenderPresent(gRenderer);
			SDL_GL_SwapWindow(m_Window);
		}

		m_DeltaTime = SDL_GetTicks() - startTime;
		int sleepTime = m_FrameTime - m_DeltaTime;

		if (sleepTime > 0)
		{
			SDL_Delay(sleepTime);
			m_DeltaTime += sleepTime;
		}
	}
}

void Context::Terminate()
{
	SDL_GL_DeleteContext(m_GlContext);
	SDL_DestroyWindow(m_Window);
	Mix_CloseAudio();
	SDL_Quit();
}

void Context::RegisterPostInitCallback(bool(*fnPostInit)())
{
	m_FnPostInit = fnPostInit;
}

void Context::RegisterUpdateCallback(void(*fnUpdate)(float dt))
{
	m_FnUpdate = fnUpdate;
}

void Context::RegisterRenderCallback(void(*fnRender)())
{
	m_FnRender = fnRender;
}

void Context::RegisterKeyDownCallback(void(*fnKeyDown)(int key))
{
	m_FnKeyDown = fnKeyDown;
}

void Context::RegisterKeyUpCallback(void(*fnKeyUp)(int key))
{
	m_FnKeyUp = fnKeyUp;
}

void Context::RegisterMouseDownCallback(void(*fnMouseDown)(int key, int xPos, int yPos))
{
	m_FnMouseDown = fnMouseDown;
}

void Context::RegisterMouseMotionCallback(void(*fnMouseMotion)(int xPos, int yPos))
{
	m_FnMouseMotion = fnMouseMotion;
}

void Context::RegisterMouseWheelCallback(void(*fnMouseWheel)(int xOffset, int yOffset))
{
	m_FnMouseWheel = fnMouseWheel;
}