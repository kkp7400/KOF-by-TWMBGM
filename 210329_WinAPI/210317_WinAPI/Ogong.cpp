#include "Ogong.h"
#include"Image.h"

HRESULT Ogong::Init()
{
	frame = 0;
	elapsedTime = 0;

	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y - 300;

	img = new Image();
	if (FAILED(img->Init("Image/Ogong.bmp", 4640, 228, 20, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Ogong.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void Ogong::Release()
{
	if (img)
	{
		img->Release();
		delete img;
		img = nullptr;
	}
}

void Ogong::Update()
{
	elapsedTime++;
	if (elapsedTime >= 21)
		//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		frame++;
		if (frame >= 20)
		{
			frame = 0;
		}
		elapsedTime = 0;
		//pos.x += 10;
	}
}

void Ogong::Render(HDC hdc)
{
	if (img)
	{
		img->Render(hdc, pos.x, pos.y, frame);
	}
}