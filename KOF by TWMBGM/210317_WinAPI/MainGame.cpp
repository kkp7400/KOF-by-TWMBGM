#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"
#include "Missile.h"
#include "Image.h"
#include"Iori.h"
#include "Ogong.h"
#include "Mai.h"

/*
	1. ��� bin.bmp�� ������ ���ϴ� ���Ϸ� �ٲ㺸��.
	2. ��ũ�� �߻��ϴ� �̻��Ͽ� ����.bmp�� ��������.
	3. �̿����� ȭ�� �ϴܿ� ���� 1�ʸ��� 1������(�ִϸ��̼�)�� �ٲ�� ����غ���.
*/

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();		//����ƽ�� �տ������� Ƽ�޴������ �ϴ� ������Ÿ���� ����ִ� �����Լ�
	//keyMgr.Init();
	// ���ΰ����� �ʱ�ȭ �Լ�
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);
	
	//����� �̹���
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	background = new Image();
	background->Init("Image/background.bmp", WINSIZE_X, WINSIZE_Y);		//���⿡ ������� ������ ����ũ�Ⱑ �˸°� ����.(������ ����ũ�⸸ŭ ���ڳ־���)

	iori = new Iori();
	iori->Init();

	ogong = new Ogong();
	ogong->Init();

	mai = new Mai();
	mai->Init();

	tank = new Tank();
	tank->Init();

	// ������ ��ġ�� ����
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

	InvalidateRect(g_hWnd, NULL, false); //false���ϸ� �������� �������� ����
}

void MainGame::Render(HDC hdc)
{

	HDC hBackDC = (backBuffer->GetMemDC());
	if (background)		//������
	{
		background->Render(hBackDC/*, 0, 0*/);		//������Ͽ��� �ʱ�ȭ�� �߱� ������ 0,0�� �����ص���
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
	// �λ�
	TextOut(hBackDC, 20, 20, "MainGame ���� ��", strlen("MainGame ���� ��"));
	// ���콺 ��ǥ
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
	// �� <-> ��ũ �̻��� 
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

	// �� <-> ��ũ

	// �� �̻��� <-> ��ũ

	// �� �̻��� <-> ��ũ �̻���
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
