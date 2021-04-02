#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"

HRESULT Enemy::Init()
{
    pos.x =  0.0f;
    pos.y = 0.0f;
    size = 80;
    name = "NormalEnemy";
    shape = { 0, 0, 0, 0 };
    moveSpeed = 3.3f;
    isAlive = true;
    angle = 0.0f;
    target = nullptr;
    dir = 1;

    return S_OK;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
    if (isAlive)
    {
        HorizonMove();
        //Move();
    }
}

void Enemy::Render(HDC hdc)
{
    if (isAlive)
    {
        RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);
    }
}

void Enemy::Move()
{
    if (target)
    {
        FPOINT targetPos = target->GetPos();

        // ���� ��ġ���� Ÿ�� ��ġ�� �̵��� �� �ִ� ���� ���ϱ�
        float x = targetPos.x - pos.x;
        float y = targetPos.y - pos.y;

        angle = atan2(y, x);

        pos.x += cosf(angle) * moveSpeed;
        pos.y += sinf(angle) * moveSpeed;
    }
}

void Enemy::HorizonMove()
{
    if (pos.x > WINSIZE_X || pos.x < 0)
    {
        dir *= -1;
    }
    pos.x += moveSpeed * dir;
}
