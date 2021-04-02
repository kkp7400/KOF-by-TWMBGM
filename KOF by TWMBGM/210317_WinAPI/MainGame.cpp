#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"
#include "Missile.h"
#include "Image.h"
#include"Iori.h"
#include "Ogong.h"
#include "Mai.h"

/*
	1. 배경 bin.bmp를 본인이 원하는 파일로 바꿔보자.
	2. 탱크가 발사하는 미사일에 구슬.bmp를 씌워보자.
	3. 이오리를 화면 하단에 띄우고 1초마다 1프레임(애니메이션)씩 바뀌게 출력해보자.
*/

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();		//스테틱이 앞에있으면 티메니저라고 하는 데이터타입이 들고있는 공용함수
	//keyMgr.Init();
	// 메인게임의 초기화 함수
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);
	
	//백버퍼 이미지
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	background = new Image();
	background->Init("Image/background.bmp", WINSIZE_X, WINSIZE_Y);		//여기에 윈사이즈를 넣으면 사진크기가 알맞게 들어간다.(원래는 사진크기만큼 숫자넣어줌)

	iori = new Iori();
	iori->Init();

	ogong = new Ogong();
	ogong->Init();

	mai = new Mai();
	mai->Init();

	tank = new Tank();
	tank->Init();

	// 랜덤한 위치로 셋팅
	srand(time(NULL));
	FPOINT randPos;
	enemyCount = 1;
	enemy = new Enemy[enemyCount];
	for (int i = 0; i < enemyCount; i++)
	{
		enemy[i].Init();
		enemy[i].SetTarget(tank);

		randPos.x = rand() % WINSIZE_X;
		randPos.y = rand() % 200;
		enemy[i].SetPos(randPos);
	}


	isInited = true;

	return S_OK;
}

void MainGame::Release()
{
	for (int i = 0; i < enemyCount; i++)
	{
		enemy[i].Release();
	}
	delete[] enemy;
	enemy = nullptr;

	tank->Release();
	delete tank;
	tank = nullptr;
	KeyManager::GetSingleton()->Release();

	backBuffer->Release();
	delete backBuffer;
	backBuffer = nullptr;

	//Iori->Release();
	//delete	Iori;
	//Iori = nullptr;

	iori->Release();
	delete iori;
	iori = nullptr;

	ogong->Release();
	delete ogong;
	ogong = nullptr;


	mai->Release();
	delete mai;
	mai = nullptr;

	KillTimer(g_hWnd, 0);
}

void MainGame::Update()
{
	if (tank)
	{
		tank->Update();
	}

	if (enemy)
	{
		for (int i = 0; i < enemyCount; i++)
		{
			enemy[i].Update();
		}
	}
	if (iori)
	{
		iori->Update();
	}

	if (ogong)
	{
		ogong->Update();
	}

	if (mai)
	{
		mai->Update();
	}

	CheckCollision();

	InvalidateRect(g_hWnd, NULL, false); //false로하면 배경사진은 깜박이지 않음
}

void MainGame::Render(HDC hdc)
{

	HDC hBackDC = (backBuffer->GetMemDC());
	if (background)		//원빈배경
	{
		background->Render(hBackDC/*, 0, 0*/);		//헤더파일에서 초기화를 했기 때문에 0,0은 삭제해도됨
	}

	//if (Iori)
	//{
	//	Iori->Render(hBackDC, 68*(ioriCnt/5), 0,68);
	//}
	
	if (iori)
	{
		iori->Render(hBackDC);
	}

	if (ogong)
	{
		ogong->Render(hBackDC);
	}

	if (mai)
	{
		mai->Render(hBackDC);
	}
	// 인사
	TextOut(hBackDC, 20, 20, "MainGame 렌더 중", strlen("MainGame 렌더 중"));
	// 마우스 좌표
	wsprintf(szText, "X : %d, Y : %d", ptMouse.x, ptMouse.y);
	TextOut(hBackDC, 200, 20, szText, strlen(szText));

	if (tank)
	{
		tank->Render(hBackDC);
	}
	if (iori)
	{
		iori->Render(hBackDC);
	}

	if (enemy)
	{
		for (int i = 0; i < enemyCount; i++)
		{
			enemy[i].Render(hBackDC);
		}
	}


	backBuffer->Render(hdc, 0, 0);
}



void MainGame::CheckCollision()
{
	// 적 <-> 탱크 미사일 
	float distance;
	FPOINT enemyPos;
	FPOINT missilePos;
	float x, y;
	int r1, r2;
	Missile* missileArray = tank->GetMissile();

	for (int i = 0; i < enemyCount; i++)
	{
		if (enemy[i].GetIsAlive() == false)	continue;

		for (int j = 0; j < tank->GetMissileCount(); j++)
		{
			if (missileArray[j].GetIsFired() == false)	continue;

			enemyPos = enemy[i].GetPos();
			missilePos = missileArray[j].GetPos();

			x = enemyPos.x - missilePos.x;
			y = enemyPos.y - missilePos.y;

			distance = sqrtf(x * x + y * y);

			r1 = enemy[i].GetSize() / 2;
			r2 = missileArray[j].GetSize() / 2;

			if (distance <= r1 + r2)
			{
				enemy[i].SetIsAlive(false);
				missileArray[j].SetIsFired(false);
				break;
			}
		}
	}

	// 적 <-> 탱크

	// 적 미사일 <-> 탱크

	// 적 미사일 <-> 탱크 미사일
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		if (isInited)
		{
			this->Update();
		}
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		if (isInited)
		{
			this->Render(hdc);
		}

		EndPaint(g_hWnd, &ps);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}
