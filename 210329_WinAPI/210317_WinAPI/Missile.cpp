#include "Missile.h"
#include "Enemy.h"
#include "CommonFunction.h"
#include"Image.h"

HRESULT Missile::Init()
{
	pos = {-100, -100};
	moveSpeed = 5.0f;
	size = 50;
	shape = { 0, 0, 0, 0 };
	damage = 5000;
	angle = 0.0f;
	isFired = false;
	missileType = TYPE::Normal;
	fireStep = 0;
	target = nullptr;
	destAngle = 0.0f;

	Missileimg = new Image();
	Missileimg->Init("Image/구슬.bmp", size, size, true, RGB(255, 0, 255));
    return S_OK;
}

void Missile::Release()
{
	if (Missileimg)
	{
		Missileimg->Release();
		delete Missileimg;
		Missileimg = nullptr;
	}
	//delete
}

void Missile::Update()
{
	// 위치 이동
	if (isFired)
	{
		switch (missileType)
		{
		case TYPE::Normal:
			MovingNormal();
			break;
		case TYPE::Skill_01:
			MovingSkill_01();
			break;
		case TYPE::FollowTarget:
			MovingFollowTarget();
			break;
		}

		if (pos.x < 0 || pos.y < 0 || pos.x > WINSIZE_X || pos.y > WINSIZE_Y)
		{
			isFired = false;
			fireStep = 0;
		}
	}

	shape.left = pos.x - size / 2;
	shape.top = pos.y - size / 2;
	shape.right = pos.x + size / 2;
	shape.bottom = pos.y + size / 2;
}

void Missile::Render(HDC hdc)
{
	
	if (isFired)
	{
		if (Missileimg)
		{
			Missileimg->Render(hdc, shape.left, shape.top);
			//Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
		}
	}
}

void Missile::MovingNormal()
{
	pos.x += cosf(angle) * moveSpeed;
	pos.y -= sinf(angle) * moveSpeed;
}

void Missile::MovingSkill_01()
{
	if (fireStep == 0 && pos.y < 300.0f)
	{
		angle = fireIndex * 3.14f * 2.0f / 36.0f;
		fireStep++;
	}

	pos.x += cosf(angle) * moveSpeed;
	pos.y -= sinf(angle) * moveSpeed;
}

void Missile::MovingFollowTarget()
{
	if (target)
	{
		destAngle = GetAngle(pos, target->GetPos());
		float ratio = (destAngle - angle) / 15.0f;

		if (-0.05f < ratio && ratio < 0.05f)
		{
			angle = destAngle;
		}
		else
		{
			angle += ratio;
		}
	}

	pos.x += cosf(angle) * moveSpeed;
	pos.y += sinf(angle) * moveSpeed;
}
