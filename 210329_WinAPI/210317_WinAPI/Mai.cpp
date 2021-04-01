#include "Mai.h"
#include "Image.h"

HRESULT Mai::Init()
{
	//애니메이션 별 변경 값
	maxFrame = 48; // 프레임 수
	//여기까지
	frame = 0;
	elapedTime = 0;
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y - 500;
	state = Idle;
	canState = TRUE;
	//기본
	img_Idle = new Image();
	if (FAILED(img_Idle->Init("Image/Mai_Idle.bmp", 9408, 228, 48, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Mai_Idle.bmp", NULL, NULL);
		return E_FAIL;
	}
	//앞으로 이동
	img_Front_walk = new Image();
	if (FAILED(img_Front_walk->Init("Image/Mai_Front_Walk.bmp", 2200, 240, 10, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Mai_Front_Walk.bmp", NULL, NULL);
		return E_FAIL;
	}
	//뒤로 이동
	img_Back_walk = new Image();
	if (FAILED(img_Back_walk->Init("Image/Mai_Back_Walk.bmp", 2200, 240, 10, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Mai_Back_Walk.bmp", NULL, NULL);
		return E_FAIL;
	}
	img_foot_Strong_Attack = new Image();
	if (FAILED(img_foot_Strong_Attack->Init("Image/Foot_Strong_Attack.bmp", 4760, 260, 14 , 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Foot_Strong_Attack.bmp", NULL, NULL);
		return E_FAIL;
	}
	img_foot_Weak_Attack  = new Image();
	img_fist_Strong_Attack = new Image();
	img_fist_Weak_Attack  = new Image();

	return S_OK;
}

void Mai::Release()
{

	if (img_Idle)
	{
		img_Idle->Release();
		delete img_Idle;
		img_Idle = nullptr;
	}
	if (img_Front_walk)
	{
		img_Front_walk->Release();
		delete img_Front_walk;
		img_Front_walk = nullptr;
	}
	if (img_Back_walk)
	{
		img_Back_walk->Release();
		delete img_Back_walk;
		img_Back_walk = nullptr;
	}
	if (img_foot_Strong_Attack)
	{
		img_foot_Strong_Attack->Release();
		delete img_foot_Strong_Attack;
		img_foot_Strong_Attack = nullptr;
	}
}

void Mai::Update()
{

	if (KeyManager::GetSingleton()->IsStayKeyDown('B') && canState == TRUE)
	{
		state = Front;
		maxFrame = 10;
		pos.x--;
		canState = TRUE;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp('B') && canState == TRUE)
	{
		state = Idle;
		maxFrame = 48;
		canState = TRUE;
	}


	if (KeyManager::GetSingleton()->IsStayKeyDown('M') && canState == TRUE)
	{
		state = Back;
		maxFrame = 10;
		pos.x++;
		canState = TRUE;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp('M') && canState == TRUE)
	{
		state = Idle;
		maxFrame = 48;
		canState = TRUE;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('S') && canState == TRUE)
	{
		frame = 0;
		state = Foot_Strong_Attack;
		maxFrame = 14;
		canState = FALSE;

	}

	elapedTime++;
	
	if (elapedTime % 4 == 0&&(state == Foot_Strong_Attack))
	{
		frame++;
		if (frame >= maxFrame)
		{			
			if (frame == maxFrame)
			{
				canState = TRUE;
				state = Idle;
			}
			frame = 0;
		}
	}
	else if (elapedTime % 4 == 0)
	{
		frame++;
		if (frame >= maxFrame)
		{
			frame = 0;
			canState = TRUE;
		}
	}
}

void Mai::Render(HDC hdc)
{
	switch (state)
	{
	case Mai::Idle:
		img_Idle->Render(hdc, pos.x, pos.y, frame);
		break;
	case Mai::Front:
		img_Front_walk->Render(hdc, pos.x, pos.y, frame);
		break;
	case Mai::Back:
		img_Back_walk->Render(hdc, pos.x, pos.y, frame);
		break;
	case Mai::Foot_Strong_Attack:
		img_foot_Strong_Attack->Render(hdc, pos.x, pos.y, frame);
	case Mai::Hit:
		break;
		//case Mai::Foot_Strong_Attack:
		//	break;
		//case Mai::Foot_Weak_Attack:
		//	break;
		//case Mai::Fist_Strong_Attack:
		//	break;
		//case Mai::Fist_Weak_Attack:
		//	break;
		//case Mai::Combo_1:
		//	break;
		//case Mai::Combo_2:
		//	break;
		//case Mai::Combo_3:
		//	break;
		//case Mai::Skill_1:
		//	break;
		//default:
		//	break;
	}
}
