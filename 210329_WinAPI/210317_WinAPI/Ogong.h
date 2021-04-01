#pragma once
#include"GameNode.h"

class Image;

class Ogong :public GameNode
{
private:
	Image* img;
	FPOINT pos;
	int elapsedTime;
	int frame;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};
