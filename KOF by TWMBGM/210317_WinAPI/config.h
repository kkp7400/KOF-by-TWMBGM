// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <ctime>
//#include<set>		//값 자체가 단일(유일)하다 (예 주민등록번호, 핸드폰번호, 차번호, 몬스터id, 무기상점id)
#include<bitset>		//데이터 자체가 비트로 표현되는 것 (키가 눌렸다, 눌리지 않았다) , std필요

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