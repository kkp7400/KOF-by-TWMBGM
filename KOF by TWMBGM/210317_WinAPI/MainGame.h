#pragma once
#include "GameNode.h"

//#include"KeyManager.h"

class Mai;
class Ogong;
class Iori;
class Image;
class Tank;
class Enemy;
class MainGame : public GameNode
{
private:
	bool isInited;

	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	POINT ptMouse{ 0, 0 };
	char szText[128] = "";

	Image* backBuffer;
	Image* bin;
	Image* background;
	Image* Missileimg;
	//Image* Iori;
	//int ioriCnt;

	Ogong* ogong;

	Iori* iori;

	Mai* mai;

	Tank* tank;

	int enemyCount;
	Enemy* enemy;
	//KeyManager keyMgr;

public:
	HRESULT Init();		// 오버라이딩 : 다형성
	void Release();
	void Update();
	void Render(HDC hdc);	
	void CheckCollision();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

