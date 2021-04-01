#pragma once

#include "Singleton.h"

#define MAX_KEY_COUNT 256

using namespace std;

class KeyManager :public Singleton <KeyManager> //키메니저를 만들때 싱글톤을 상속받고 싱글톤은 키매니저를 데이터 타입으로 씀
{
private:

	//static KeyManager* instance;		//이렇게 있다.

	bitset<MAX_KEY_COUNT> keyUp;		//키 갯수만큼 사이즈를 <>에 넣어준다(사이즈만큼 공간을 할당하기 때문에 배열로도 사용가능) 현재 키가 위로 올라와 있는지
	bitset<MAX_KEY_COUNT> keyDown;		//현재 키가 눌려 있는지

	
public:
	HRESULT Init();
	void Release();
	
	bool IsOnceKeyDown(int key);			//해당 키가 처음 눌렸는지 판단하는 함수
	bool IsOnceKeyUp(int key);				//해당 키가 눌렸다가 처음 떼어졌는지
	bool IsStayKeyDown(int key);			//해당 키가 계속 눌려있는지 판단하는 함수
	bool IsStayKeyUp(int key);

	void SetKeyDown(int key, bool state) { this->keyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { this->keyUp.set(key, state); }
};

