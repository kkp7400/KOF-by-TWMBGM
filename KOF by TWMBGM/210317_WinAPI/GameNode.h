#pragma once
#include "config.h"
// 멤버 변수, 멤버 함수 원형 등이 선언

/*
	앞으로 만들어질 게임구조의 가장 기본이 되는 클래스
*/
class GameNode
{
public:
	HRESULT Init();			// 멤버 변수의 초기화, 메모리 할당
	void Release();			// 메모리 해제
	void Update();			// 프레임 단위로 게임 로직 실행 (데이터 변동)
	void Render(HDC hdc);	// 프레임 단위로 출력 (이미지, 텍스트 등)

	GameNode();
	~GameNode();
};

