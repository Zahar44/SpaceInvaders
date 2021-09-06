#include <windows.h>
#include <string>

#include "Game.h"

Game* app = NULL;

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	app = new Game(hInst);
	app->Start();

	delete app;
}
