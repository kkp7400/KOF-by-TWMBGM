// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <ctime>
//#include<set>		//�� ��ü�� ����(����)�ϴ� (�� �ֹε�Ϲ�ȣ, �ڵ�����ȣ, ����ȣ, ����id, �������id)
#include<bitset>		//������ ��ü�� ��Ʈ�� ǥ���Ǵ� �� (Ű�� ���ȴ�, ������ �ʾҴ�) , std�ʿ�

#include "KeyManager.h"

using namespace std;

#define WINSIZE_X	1600
#define WINSIZE_Y	900

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

//typedef tagFPoint FPOINT2;
//typedef tagFPoint* PFPOINT2;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;