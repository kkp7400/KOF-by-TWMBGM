#pragma once

#include "Singleton.h"

#define MAX_KEY_COUNT 256

using namespace std;

class KeyManager :public Singleton <KeyManager> //Ű�޴����� ���鶧 �̱����� ��ӹް� �̱����� Ű�Ŵ����� ������ Ÿ������ ��
{
private:

	//static KeyManager* instance;		//�̷��� �ִ�.

	bitset<MAX_KEY_COUNT> keyUp;		//Ű ������ŭ ����� <>�� �־��ش�(�����ŭ ������ �Ҵ��ϱ� ������ �迭�ε� ��밡��) ���� Ű�� ���� �ö�� �ִ���
	bitset<MAX_KEY_COUNT> keyDown;		//���� Ű�� ���� �ִ���

	
public:
	HRESULT Init();
	void Release();
	
	bool IsOnceKeyDown(int key);			//�ش� Ű�� ó�� ���ȴ��� �Ǵ��ϴ� �Լ�
	bool IsOnceKeyUp(int key);				//�ش� Ű�� ���ȴٰ� ó�� ����������
	bool IsStayKeyDown(int key);			//�ش� Ű�� ��� �����ִ��� �Ǵ��ϴ� �Լ�
	bool IsStayKeyUp(int key);

	void SetKeyDown(int key, bool state) { this->keyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { this->keyUp.set(key, state); }
};

