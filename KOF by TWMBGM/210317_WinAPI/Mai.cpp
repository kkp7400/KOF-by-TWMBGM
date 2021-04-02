#include "Mai.h"
#include "Image.h"
#include <iostream>
/*	☆☆☆☆필독
			중요한 사실
			프로젝트 명: KOF by TWMBGM
			설명: TWMBGM은 [세계 제일 미녀 마이]를 의미 합니다.
			팀원: 배현성, 우성현, 김지유			

*/
// 이미지 반전 할거면 전용 함수를 쓰기는 어려워보이고 반전 이미지를 그림판으로 만들고 뒤에서 부터 읽어야 할듯?
// 캐릭터 거의 끝남 발사체 하면 저는 끝!
HRESULT Mai::Init()
{
	//#region 이라는 기능인데 함수 쓴거처럼 접을 수 있네요. 이럴거면 굳이 함수화 필요한가? 이걸로 충분히 가독성 좋아보이는데... 암튼 중간에 알게되어 사용해봄
	#pragma region startSetting
	//애니메이션 별 변경 값
	maxFrame = 16; // 프레임 수
	//여기까지
	frame = 0;
	elapedTime = 0;
	pos.x = WINSIZE_X - 800;
	pos.y = WINSIZE_Y - 500;
	state = Idle;
	canState = TRUE;
	command[0] = '0';
	command[1] = '0';
	command[2] = '0';
	command[3] = '0';
	commandTime = 0;
	cinCommand = '0';
	countCommand = 0;
	#pragma endregion
	//기본
	#pragma region imageInit
	img_Idle = new Image();
	if (FAILED(img_Idle->Init("Image/Mai/Mai_Idle.bmp", 6400, 400, 16, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Mai/Mai_Idle.bmp", NULL, NULL);
		return E_FAIL;
	}
	//앞으로 이동
	img_Front_walk = new Image();
	if (FAILED(img_Front_walk->Init("Image/Mai/Mai_Front_Walk.bmp", 3666, 400, 10, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Mai/Mai_Front_Walk.bmp", NULL, NULL);
		return E_FAIL;
	}
	//뒤로 이동
	img_Back_walk = new Image();
	if (FAILED(img_Back_walk->Init("Image/Mai/Mai_Back_Walk.bmp", 3666, 400, 10, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Mai/Mai_Back_Walk.bmp", NULL, NULL);
		return E_FAIL;
	}
	img_foot_Strong_Attack = new Image();
	if (FAILED(img_foot_Strong_Attack->Init("Image/Mai/Foot_Strong_Attack.bmp", 3511*1.7, 320*1.7, 11 , 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Mai/Foot_Strong_Attack.bmp", NULL, NULL);
		return E_FAIL;
	}
	img_foot_Weak_Attack  = new Image();
	if (FAILED(img_foot_Weak_Attack->Init("Image/Mai/Foot_Weak_Attack.bmp", 4736*1.6, 260*1.6, 14, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Mai/Foot_Weak_Attack.bmp", NULL, NULL);
		return E_FAIL;
	}
	img_fist_Strong_Attack = new Image();
	if (FAILED(img_fist_Strong_Attack->Init("Image/Mai/Fist_Strong_Attack.bmp", 4392*1.1, 396*1.1, 10, 1, true, RGB(144, 144, 144))))
	{
		MessageBox(g_hWnd, "Image/Mai/Fist_Strong_Attack.bmp", NULL, NULL);
		return E_FAIL;
	}
	img_fist_Weak_Attack  = new Image();
	if (FAILED(img_fist_Weak_Attack->Init("Image/Mai/Fist_Weak_Attack.bmp", 2307*1.1, 325*1.1, 6, 1, true, RGB(144, 144, 144))))
	{
		MessageBox(g_hWnd, "Image/Mai/Fist_Weak_Attack.bmp", NULL, NULL);
		return E_FAIL;
	}
	img_Skill_1 = new Image();
	if (FAILED(img_Skill_1->Init("Image/Mai/Skill_1.bmp", 8876, 400, 18, 1, true, RGB(255,255,255))))
	{
		MessageBox(g_hWnd, "Image/Mai/Skill_1.bmp", NULL, NULL);
		return E_FAIL;
	}
#pragma endregion
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
	if (img_foot_Weak_Attack)
	{
		img_foot_Weak_Attack->Release();
		delete img_foot_Weak_Attack;
		img_foot_Weak_Attack = nullptr;
	}
	if (img_fist_Strong_Attack)
	{
		img_fist_Strong_Attack->Release();
		delete img_fist_Strong_Attack;
		img_fist_Strong_Attack = nullptr;
	}
	if (img_fist_Weak_Attack)
	{
		img_fist_Weak_Attack->Release();
		delete img_fist_Weak_Attack;
		img_fist_Weak_Attack = nullptr;
	}
	if (img_Skill_1)
	{
		img_Skill_1->Release();
		delete img_Skill_1;
		img_Skill_1 = nullptr;
	}
}
// 무브, 어택, 리셋 커맨드 함수로 이루어져 있습니다.
void Mai::Update()
{

	Move();
	Attack();
	#pragma region aniFrameUpdate
	elapedTime++;	
	if (elapedTime % 4 == 0&&(
		state == Foot_Strong_Attack||
		state == Foot_Weak_Attack||
		state == Fist_Strong_Attack||
		state == Fist_Weak_Attack||
		state == Skill_1))
	{
		frame++;
		;
		if (frame >= maxFrame)
		{			
			if (frame == maxFrame)
			{
				canState = TRUE;
				state = Idle;
				maxFrame = 16;
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
	commandTime++;
	if (commandTime > 1000 || countCommand >= 4)
	{
		ResetCommand('0');
		std::cout << "들어옴" << endl;
	}	
	for (int i = 0; i < 4; i++)
	{
		std::cout << "command " << i << " : " << command[i] << endl;
	}
	#pragma endregion
}
// 이미지를 렌더합니다.
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
		img_foot_Strong_Attack->Render(hdc, pos.x-60, pos.y-125, frame);
		break;
	case Mai::Foot_Weak_Attack:
		img_foot_Weak_Attack->Render(hdc, pos.x-150, pos.y-20, frame);
		break;		
	case Mai::Fist_Strong_Attack:
		img_fist_Strong_Attack->Render(hdc, pos.x-65, pos.y-48, frame);
		break;
	case Mai::Fist_Weak_Attack:
		img_fist_Weak_Attack->Render(hdc, pos.x-90, pos.y+30, frame);
		break;
	case Mai::Skill_1:
		img_Skill_1->Render(hdc, pos.x-40, pos.y-15, frame);
		break;
	}
}
// 이동 관련입니다.
void Mai::Move()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown('B') && canState == TRUE)
	{
		state = Front;
		maxFrame = 10;
		pos.x -= 2;
		canState = TRUE;

	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp('B') && canState == TRUE)
	{
		state = Idle;
		maxFrame = 16;
		canState = TRUE;
		countCommand++;
		cinCommand = 'B';

		if (countCommand != 1 && countCommand != 3)
		{
			ResetCommand('B');
		}
		else
		{
			if (countCommand == 3)
				std::cout << "들어옴" << endl;

			command[countCommand - 1] = 'B';
			commandTime = 0;
		}
	}


	if (KeyManager::GetSingleton()->IsStayKeyDown('M') && canState == TRUE)
	{
		state = Back;
		maxFrame = 10;
		pos.x += 2;
		canState = TRUE;

	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp('M') && canState == TRUE)
	{
		state = Idle;
		maxFrame = 16;
		canState = TRUE;
		countCommand++;
		cinCommand = 'M';

		if (countCommand != 2)
		{
			ResetCommand('M');
		}
		else
		{
			command[countCommand - 1] = 'M';
			commandTime = 0;
		}
	}
}
// 여기 공격 및 커맨드 관련 들어 있습니다.
void Mai::Attack()
{

	if (KeyManager::GetSingleton()->IsOnceKeyDown('S') && canState == TRUE)
	{
		frame = 0;
		state = Foot_Strong_Attack;
		maxFrame = 11;
		canState = FALSE;

	}


	if (KeyManager::GetSingleton()->IsOnceKeyDown('A') && canState == TRUE)
	{
		frame = 0;
		state = Foot_Weak_Attack;
		maxFrame = 14;
		canState = FALSE;

	}


	if (KeyManager::GetSingleton()->IsOnceKeyDown('W') && canState == TRUE)
	{
		countCommand++;

		if (countCommand != 4)
		{
			ResetCommand('W');
		}
		else
		{
			command[countCommand - 1] = 'W';
		}

		if (command[0] == 'B' &&
			command[1] == 'M' &&
			command[2] == 'B' &&
			command[3] == 'W' && canState == TRUE)
		{
			frame = 0;
			state = Skill_1;
			maxFrame = 18;
			canState = FALSE;
		}
		else if (state != Skill_1)
		{
			frame = 0;
			state = Fist_Strong_Attack;
			maxFrame = 10;
			canState = FALSE;
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('Q') && canState == TRUE)
	{
		frame = 0;
		state = Fist_Weak_Attack;
		maxFrame = 6;
		canState = FALSE;

	}
}
// 커맨드 오입력 시 초기화 카운트 현재 커맨드의 최대 카운트를 4로 해놓아서 4개의 값만 받습니다. 추가 시 해당 부분도 변경해주세요.
void Mai::ResetCommand(char lastCharacter)
{
	command[0] = lastCharacter;
	command[1] = '0';
	command[2] = '0';
	command[3] = '0';
	countCommand = 0;
	commandTime = 0;
}