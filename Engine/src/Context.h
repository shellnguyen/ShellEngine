#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "SDL.h"
#include "SDL_mixer.h"
#include "GL\glew.h"

class Context
{
private:
	SDL_Window* m_Window;
	SDL_GLContext m_GlContext;

	Uint32			m_FPS = 0;
	Uint32			m_FrameTime = 0;
	Uint32			m_DeltaTime = 0;

	bool(*m_FnPostInit)() = NULL;
	void(*m_FnUpdate)(float) = NULL;
	void(*m_FnRender)() = NULL;
	void(*m_FnKeyDown)(int) = NULL;
	void(*m_FnKeyUp)(int) = NULL;
	void(*m_FnMouseDown)(int, int, int) = NULL;
	void(*m_FnMouseMotion)(int, int) = NULL;
	void(*m_FnMouseWheel)(int, int) = NULL;

	Context();
	~Context() = default;
	Context(const Context &o) = delete;
	Context& operator=(Context& o) = delete;

	static Context* m_Instance;

public:
	static Context* GetInstance();

	bool Initialize(int width, int height);
	void SetFPS(Uint32 fps);
	void GameLoop();
	void Terminate();

	void RegisterPostInitCallback(bool(*fnPostInit)());
	void RegisterUpdateCallback(void(*fnUpdate)(float dt));
	void RegisterRenderCallback(void(*fnRender)());
	void RegisterKeyDownCallback(void(*fnKeyDown)(int key));
	void RegisterKeyUpCallback(void(*fnKeyUp)(int key));
	void RegisterMouseDownCallback(void(*fnMouseDown)(int key, int xPos, int yPos));
	void RegisterMouseMotionCallback(void(*fnMouseMotion)(int xPos, int yPos));
	void RegisterMouseWheelCallback(void(*fnMouseWheel)(int xOffset, int yOffset));
};

#endif // !_CONTEXT_H_

