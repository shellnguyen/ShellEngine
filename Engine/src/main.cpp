#include <string>
#include "Context.h"

bool Init();
void OnRender();
void OnUpdate(float dt);
void OnKeyDown(int keyCode);
void OnKeyUp(int keyCode);
void OnMouseDown(int key, int xPos, int yPos);
void OnMouseMotion(int xPos, int yPos);
void OnMouseWheel(int xOffet, int yOffset);
void OnExit();

int main(int argc, char *argv[])
{
	srand(NULL);
	Context::GetInstance()->Initialize(800, 600);
	Context::GetInstance()->SetFPS(60);
	Context::GetInstance()->RegisterPostInitCallback(Init);
	Context::GetInstance()->RegisterUpdateCallback(OnUpdate);
	Context::GetInstance()->RegisterRenderCallback(OnRender);
	Context::GetInstance()->RegisterKeyDownCallback(OnKeyDown);
	Context::GetInstance()->RegisterKeyUpCallback(OnKeyUp);
	Context::GetInstance()->RegisterMouseDownCallback(OnMouseDown);
	Context::GetInstance()->RegisterMouseMotionCallback(OnMouseMotion);
	Context::GetInstance()->RegisterMouseWheelCallback(OnMouseWheel);

	Context::GetInstance()->GameLoop();

	OnExit();

	return 0;
}

bool Init()
{
	return true;
}

void OnUpdate(float dt)
{
}

void OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void OnKeyDown(int key)
{
	switch (key)
	{
	case SDLK_w:
	{
		printf("Press W\n");
		break;
	}
	case SDLK_s:
	{
		printf("Press S\n");
		break;
	}
	case SDLK_a:
	{
		printf("Press A\n");
		break;
	}
	case SDLK_d:
	{
		printf("Press D\n");
		break;
	}
	}
}

void OnKeyUp(int key)
{

}

void OnMouseDown(int button, int mouseX, int mouseY)
{
	switch (button)
	{
	case SDL_BUTTON_LEFT:
	{
		break;
	}
	case SDL_BUTTON_RIGHT:
		break;
	case SDL_BUTTON_MIDDLE:
		break;
	}
}

void OnMouseMotion(int xPos, int yPos)
{

	//camera.OnMouseMotion(xoffset, yoffset);
}

void OnMouseWheel(int xOffset, int yOffset)
{
}

void OnExit()
{
	Context::GetInstance()->Terminate();
}