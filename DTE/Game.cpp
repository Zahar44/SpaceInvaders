#include <ctime>
#include <string.h>
#include <thread>
#include <chrono>
#include <typeinfo>

#include "Game.h";
#include "Drawer.h";
#include "Player.h";
#include "Invader.h";
#include "MovableContainer.h";

Game* game = NULL;

LRESULT CALLBACK Game::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
		case WM_CLOSE:
		case WM_DESTROY:
			game->Stop();
			break;
		case WM_SIZE:
			game->OnSizeChanged(hwnd);
			break;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

Game::~Game() {
	delete draw;
	delete player;
	delete items;
}

void Game::Start() {
	game = this;
	CreateWindowInternal();
	hdc = GetDC(window);
	auto hTimer = CreateWaitableTimer(NULL, TRUE, NULL); 

	if (hTimer == 0) throw std::exception("Timer not created");

	QueryPerformanceCounter(&time.end);
	while (isRunning) {
		QueryPerformanceCounter(&time.start);
		QueryPerformanceFrequency(&time.frequency);

		SetWaitableTimer(hTimer, &time.nextFrame, 0, NULL, NULL, 0);
		Simulate();
		WaitForSingleObject(hTimer, INFINITE);

		QueryPerformanceCounter(&time.end);
		CalculateTime();
	}
}

void Game::Simulate() {
	keyBoard.Update();

	ProceedMessage();
	ProceedButtons();

	Render();
}

void Game::Render() {
	draw->Background(0x000000);

	for (size_t i = 0; i < items->Count(); i++)
	{
		auto type = typeid((*items)[i]).name();
		if (type == typeid(Invader).name()) {
			dynamic_cast<Invader*>(&(*items)[i])->Play();
		}
		
		auto p = (*items)[i].GetPoint();

		if (p.x > 100 || p.x < 0 || p.y > 100 || p.y < 0)
			items->Remove((*items)[i]);
		else
			(*items)[i].Draw();
	}

	StretchDIBits(hdc, 0, 0, game->renderInfo.wigth, game->renderInfo.heigth, 0, 0, game->renderInfo.wigth, game->renderInfo.heigth, game->renderInfo.buffer, &game->bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

void Game::ProceedMessage() {
	MSG msg;
	while (PeekMessage(&msg, window, 0, 0, PM_REMOVE)) {

		switch (msg.message)
		{
		case WM_KEYDOWN:
		case WM_KEYUP:
			game->OnButtonStateChanged(msg.wParam, msg.lParam);
			break;
		default:
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			break;
		}
	}
}

void Game::CalculateTime() {
	time.count.QuadPart = time.end.QuadPart - time.start.QuadPart;
	if (time.count.QuadPart != 0) {
		time.fps.QuadPart = time.frequency.QuadPart / time.count.QuadPart;
	}
	time.nextFrame.QuadPart = -166666 / 2; // ~60 fps

	//OutputDebugStringW((L"FPS: " + std::to_wstring(time.fps.QuadPart) + L'\n').c_str());
}




void Game::OnSizeChanged(HWND& hwnd) {
	RECT rect;
	GetClientRect(hwnd, &rect);
	game->renderInfo.wigth = rect.right - rect.left;
	game->renderInfo.heigth = rect.bottom - rect.top;

	if (game->renderInfo.buffer) VirtualFree(game->renderInfo.buffer, 0, MEM_RELEASE);

	int size = game->renderInfo.heigth * game->renderInfo.wigth * sizeof(int);
	game->renderInfo.buffer = VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE);

	game->bitmapInfo.bmiHeader.biSize = sizeof(game->bitmapInfo.bmiHeader);
	game->bitmapInfo.bmiHeader.biWidth = game->renderInfo.wigth;
	game->bitmapInfo.bmiHeader.biHeight = game->renderInfo.heigth;
	game->bitmapInfo.bmiHeader.biPlanes = 1;
	game->bitmapInfo.bmiHeader.biBitCount = 32;
	game->bitmapInfo.bmiHeader.biCompression = BI_RGB;

	draw->Resize();
	Render(); // force to render
}

void Game::OnButtonStateChanged(WPARAM& wParam, LPARAM& lParam) {
	KeyBoard::Key key = keyBoard.getKey(wParam);
	if(key != KeyBoard::Key::END)
		keyBoard.Update(key, lParam);
}

void Game::ProceedButtons() {
	for (size_t i = 0; i < KeyBoard::END; i++)
	{
		auto key = (KeyBoard::Key)i;
		switch (key)
		{
		case KeyBoard::Key::LEFT:
			if (keyBoard.IsDown(key))
				player->ApplyForce({ -200, 0 });
			break;
		case KeyBoard::Key::RIGHT:
			if (keyBoard.IsDown(key))
				player->ApplyForce({ 200, 0 });
			break;
		case KeyBoard::Key::UP:
		case KeyBoard::Key::SPACE:
			if (keyBoard.IsDownOnce(key))
				player->Shoot({ 1, 2 });
			break;
		default:
			break;
		}
	}
}






void Game::Init(HINSTANCE hInst) {
	items = new MovableContainer();
	draw = new Drawer(this);
	player = new Player((*this).GetItems(), &(*this).renderInfo, (*this).draw);
	int invadresCount = 1;
	invaders = new Invader*[invadresCount];
	for (size_t i = 0; i < invadresCount; i++)
	{
		invaders[i] = new Invader[invadresCount];
		for (size_t j = 0; j < invadresCount; j++)
		{
			Point position = Point();
			position.x = 20. * (i + 1.);
			position.y = 90 - 10 * j;
			invaders[i][j] = *(new Invader((*this).GetItems(), &(*this).renderInfo, (*this).draw, position));
		}
	}

	windowClass = {};
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = L"DTE";
	windowClass.lpfnWndProc = Game::WindowProc;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	this->hInst = hInst;

	RegisterClass(&windowClass);
}

void Game::CreateWindowInternal() {
	window = CreateWindow(
		windowClass.lpszClassName,
		windowClass.lpszClassName,
		WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		renderInfo.wigth,
		renderInfo.heigth,
		0,
		0,
		hInst,
		0
	);
}


