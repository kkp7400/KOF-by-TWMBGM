#include "Mai.h"
#include "Image.h"
#include <iostream>
/*	�١١١��ʵ�
			�߿��� ���
			������Ʈ ��: KOF by TWMBGM
			����: TWMBGM�� [���� ���� �̳� ����]�� �ǹ� �մϴ�.
			����: ������, �켺��, ������			

*/
// �̹��� ���� �ҰŸ� ���� �Լ��� ����� ��������̰� ���� �̹����� �׸������� ����� �ڿ��� ���� �о�� �ҵ�?
// ĳ���� ���� ���� �߻�ü �ϸ� ���� ��!
HRESULT Mai::Init()
{
	//#region �̶�� ����ε� �Լ� ����ó�� ���� �� �ֳ׿�. �̷��Ÿ� ���� �Լ�ȭ �ʿ��Ѱ�? �̰ɷ� ����� ������ ���ƺ��̴µ�... ��ư �߰��� �˰ԵǾ� ����غ�
	#pragma region startSetting
	//�ִϸ��̼� �� ���� ��
	maxFrame = 16; // ������ ��
	//�������
	frame = 0;
	elapedTime = 0;
	pos.x = WINSIZE_X - 800;
	pos.y = WINSIZE_Y - 500;
	state = Idle;
	hitCol.left = (pos.x - 55) + 195;
	hitCol.right = (pos.x + 55) + 195;
	hitCol.top = (pos.y - 200) + 280;
	hitCol.bottom = (pos.y + 80) + 280;

	atkCol.left = 0;
	atkCol.right = 0;
	atkCol.top = 0;
	atkCol.bottom = 0;
	#pragma region imageInit
	canState = TRUE;
	command[0] = '0';
	command[1] = '0';
	command[2] = '0';
	command[3] = '0';
	commandTime = 0;
	cinCommand = '0';
	countCommand = 0;

	//�⺻
	
	img_Idle = new Image();
	if (FAILED(img_Idle->Init("Image/Mai/Mai_Idle.bmp", 6400, 400, 16, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Mai/Mai_Idle.bmp", NULL, NULL);
		return E_FAIL;
	}
	//������ �̵�
	img_Front_walk = new Image();
	if (FAILED(img_Front_walk->Init("Image/Mai/Mai_Front_Walk.bmp", 3666, 400, 10, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/Mai/Mai_Front_Walk.bmp", NULL, NULL);
		return E_FAIL;
	}
	//�ڷ� �̵�
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
void Mai::UpdateHitCol()
{
	switch (state)
	{
	case Mai::Idle:
		hitCol.left = (pos.x - 55) + 195;
		hitCol.right = (pos.x + 55) + 195;
		hitCol.top = (pos.y - 200) + 280;
		hitCol.bottom = (pos.y + 80) + 280;
		break;
	case Mai::Front:
		hitCol.left = (pos.x - 55) + 150;
		hitCol.right = (pos.x + 55) + 150;
		hitCol.top = (pos.y - 200) + 280;
		hitCol.bottom = (pos.y + 80) + 280;
		break;
	case Mai::Back:
		hitCol.left = (pos.x - 55) + 215;
		hitCol.right = (pos.x + 55) + 215;
		hitCol.top = (pos.y - 200) + 280;
		hitCol.bottom = (pos.y + 80) + 280;
		break;
	}
	
}
void Mai::UpdateAtkCol()
{
	switch (state)
	{
	case Mai::Foot_Strong_Attack:
		hitCol.left = (pos.x - 55) + 195;
		hitCol.right = (pos.x + 55) + 195;
		hitCol.top = (pos.y - 200) + 280;
		hitCol.bottom = (pos.y + 80) + 280;

		atkCol.left = (pos.x - 155) + 100;
		atkCol.right = (pos.x + 55) + 100;
		atkCol.top = (pos.y - 60) + 100;
		atkCol.bottom = (pos.y + 50) + 100;
		break;
	case Mai::Foot_Weak_Attack:
		hitCol.left = (pos.x - 55) + 195;
		hitCol.right = (pos.x + 55) + 195;
		hitCol.top = (pos.y - 200) + 280;
		hitCol.bottom = (pos.y + 80) + 280;

		atkCol.left = (pos.x - 175) + 100;
		atkCol.right = (pos.x + 55) + 100;
		atkCol.top = (pos.y - 50) + 100;
		atkCol.bottom = (pos.y + 50) + 100;
		break;
	case Mai::Fist_Strong_Attack:
		hitCol.left = (pos.x - 90) + 195;
		hitCol.right = (pos.x + 15) + 195;
		hitCol.top = (pos.y - 200) + 280;
		hitCol.bottom = (pos.y + 80) + 280;

		atkCol.left = (pos.x - 150) + 100;
		atkCol.right = (pos.x + 55) + 100;
		atkCol.top = (pos.y - 120) + 100;
		atkCol.bottom = (pos.y + 30) + 100;
		break;
	case Mai::Fist_Weak_Attack:
		hitCol.left = (pos.x - 75) + 195;
		hitCol.right = (pos.x + 55) + 195;
		hitCol.top = (pos.y - 200) + 280;
		hitCol.bottom = (pos.y + 80) + 280;

		atkCol.left = (pos.x - 175) + 100;
		atkCol.right = (pos.x + 55) + 100;
		atkCol.top = (pos.y - 10) + 100;
		atkCol.bottom = (pos.y + 50) + 100;
		break;
	case Mai::Skill_1:
		break;
	}
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
// ����, ����, ���� Ŀ�ǵ� �Լ��� �̷���� �ֽ��ϴ�.
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
				UpdateHitCol();
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
		ResetCommand();
		std::cout << "����" << endl;
	}	
	for (int i = 0; i < 4; i++)
	{
		std::cout << "command " << i << " : " << command[i] << endl;
	}
	#pragma endregion
}
// �̹����� �����մϴ�.
void Mai::Render(HDC hdc)
{
	switch (state)
	{		
	case Mai::Idle:
		Rectangle(hdc, hitCol.left, hitCol.top, hitCol.right, hitCol.bottom);		
		img_Idle->Render(hdc, pos.x, pos.y, frame);		
		break;
	case Mai::Front:
		Rectangle(hdc, hitCol.left, hitCol.top, hitCol.right, hitCol.bottom);
		img_Front_walk->Render(hdc, pos.x, pos.y, frame);
		break;
	case Mai::Back:
		Rectangle(hdc, hitCol.left, hitCol.top, hitCol.right, hitCol.bottom);
		img_Back_walk->Render(hdc, pos.x, pos.y, frame);
		break;
	case Mai::Foot_Strong_Attack:
		Rectangle(hdc, hitCol.left, hitCol.top, hitCol.right, hitCol.bottom);
		Rectangle(hdc, atkCol.left, atkCol.top, atkCol.right, atkCol.bottom);
		img_foot_Strong_Attack->Render(hdc, pos.x-60, pos.y-125, frame);
		break;
	case Mai::Foot_Weak_Attack:
		Rectangle(hdc, hitCol.left, hitCol.top, hitCol.right, hitCol.bottom);
		Rectangle(hdc, atkCol.left, atkCol.top, atkCol.right, atkCol.bottom);
		img_foot_Weak_Attack->Render(hdc, pos.x-150, pos.y-20, frame);
		break;		
	case Mai::Fist_Strong_Attack:
		Rectangle(hdc, hitCol.left, hitCol.top, hitCol.right, hitCol.bottom);
		Rectangle(hdc, atkCol.left, atkCol.top, atkCol.right, atkCol.bottom);
		img_fist_Strong_Attack->Render(hdc, pos.x-65, pos.y-48, frame);
		break;
	case Mai::Fist_Weak_Attack:
		Rectangle(hdc, hitCol.left, hitCol.top, hitCol.right, hitCol.bottom);
		Rectangle(hdc, atkCol.left, atkCol.top, atkCol.right, atkCol.bottom);
		img_fist_Weak_Attack->Render(hdc, pos.x-90, pos.y+30, frame);
		break;
	case Mai::Skill_1:
		img_Skill_1->Render(hdc, pos.x-40, pos.y-15, frame);
		break;
	}
}
// �̵� �����Դϴ�.
void Mai::Move()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown('B') && canState == TRUE)
	{
		state = Front;
		UpdateHitCol();
		maxFrame = 10;
		pos.x -= 2;
		canState = TRUE;

	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp('B') && canState == TRUE)
	{
		state = Idle;
		UpdateHitCol();//�� Ŀ�ǵ�� BMBW
		maxFrame = 16;
		canState = TRUE;
		countCommand++;//ī��Ʈ Ŀ�ǵ� +1
		cinCommand = 'B';

		if (countCommand != 1 && countCommand != 3)
		{
			ResetCommand();
		}
		else
		{
			if (countCommand == 1)
			{
				command[countCommand - 1] = 'B';
				commandTime = 0;
			}
			if (countCommand == 3)
			{
				command[countCommand - 1] = 'B';
				commandTime = 0;
			}
		}
	}


	if (KeyManager::GetSingleton()->IsStayKeyDown('M') && canState == TRUE)
	{
		state = Back;
		UpdateHitCol();
		maxFrame = 10;
		pos.x += 2;
		canState = TRUE;

	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp('M') && canState == TRUE)
	{
		state = Idle;
		UpdateHitCol();
		maxFrame = 16;
		canState = TRUE;
		countCommand++;
		cinCommand = 'M';

		if (countCommand != 2)
		{
			ResetCommand();
		}
		else
		{
			command[countCommand - 1] = 'M';
			commandTime = 0;
		}
	}
}
// ���� ���� �� Ŀ�ǵ� ���� ��� �ֽ��ϴ�.
void Mai::Attack()
{

	if (KeyManager::GetSingleton()->IsOnceKeyDown('S') && canState == TRUE)
	{
		frame = 0;
		state = Foot_Strong_Attack;
		UpdateHitCol();
		UpdateAtkCol();
		maxFrame = 11;
		canState = FALSE;

	}


	if (KeyManager::GetSingleton()->IsOnceKeyDown('A') && canState == TRUE)
	{
		frame = 0;
		state = Foot_Weak_Attack;
		UpdateHitCol();
		UpdateAtkCol();
		maxFrame = 14;
		canState = FALSE;

	}


	if (KeyManager::GetSingleton()->IsOnceKeyDown('W') && canState == TRUE)
	{
		countCommand++;// ����� ���� ��� ���� 4

		if (countCommand != 4)
		{
			ResetCommand();
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
			UpdateHitCol();
			UpdateAtkCol();
			maxFrame = 10;
			canState = FALSE;
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('Q') && canState == TRUE)
	{
		frame = 0;
		state = Fist_Weak_Attack;
		UpdateHitCol();
		UpdateAtkCol();
		maxFrame = 6;
		canState = FALSE;

	}
}
// Ŀ�ǵ� ���Է� �� �ʱ�ȭ ī��Ʈ ���� Ŀ�ǵ��� �ִ� ī��Ʈ�� 4�� �س��Ƽ� 4���� ���� �޽��ϴ�. �߰� �� �ش� �κе� �������ּ���.
void Mai::ResetCommand()
{
	command[0] = '0';
	command[1] = '0';
	command[2] = '0';
	command[3] = '0';
	countCommand = 0;
	commandTime = 0;
}