#pragma once

#include <windows.h>
#include <string>

#include "KeyBoard.h";
#include "Bitmap.h"

class Player;
class Drawer;
class Invader;
class MovableContainer;

class Game
{
public:
	struct RenderInfo {
		int wigth = 1280, heigth = 720;
		double delta = 1;
		void* buffer = nullptr;
	} renderInfo;

	Game(HINSTANCE hInst) {
		isRunning = true;
		keyBoard = KeyBoard();

		Init(hInst);
	}
	~Game();

	void Start();
	void Stop() {
		isRunning = false;
	}

	MovableContainer* GetItems() {
		return items;
	}

	BITMAPINFO bitmapInfo;
private:
	WNDCLASS windowClass;
	HWND window;
	HINSTANCE hInst;
	HDC hdc;
	
	Drawer* draw;
	KeyBoard keyBoard;
	
	MovableContainer* items;
	Player* player;
	Invader** invaders;

	struct SimulationTime {
		LARGE_INTEGER start, end, count, frequency, fps;
		LARGE_INTEGER nextFrame;
	} time;

	bool isRunning;

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void Init(HINSTANCE hInst);
	void CreateWindowInternal();
	void CalculateTime();
	void Simulate();
	void ProceedMessage();
	void Render();

	void OnSizeChanged(HWND& hwnd);
	void OnButtonStateChanged(WPARAM& wParam, LPARAM& lParam);
	void ProceedButtons();
};

