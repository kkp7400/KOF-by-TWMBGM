#include "config.h"
#include "KeyManager.h"



HRESULT KeyManager::Init()
{
    keyUp.set();        //1�� ����
    keyDown.reset();    //0���� ����

    //for (int i = 0; i < MAX_KEY_COUNT; i++)
    //{
    //    keyUp[i] = true;
    //    keyDown[i] = false;
    //}
    return S_OK;
}

void KeyManager::Release()
{
    ReleaseSingleton();
}

bool KeyManager::IsOnceKeyDown(int key)
{
    /*
        GetAsyncKeyState(VK_...) <- ���� Ű�� � �������� (�ϵ���� �ӵ���=������)�˷���
        
        �Լ� ȣ�� ������ ����Ű(VK_...)�� � �������� Ȯ��
        1. 0x0000(16����) -> ���� �����ӿ� ���� ���� ���� ȣ��������� �������� ����
        2. 0x0001 -> ���� �����ӿ� �������� �ְ� ȣ��������� �������� ����
        3. 0x8000 -> ���� �����ӿ� �������� ���� ȣ��������� �����ִ� ����
        0x8 �������� �ٲٸ�-> 1000
        4. 0x8001 -> ���� �����ӿ� �������� �ְ� ȣ��������� �����ִ� ���� 

    */

    if (GetAsyncKeyState(key) & 0x8000) // & ��Ʈ������ ->��Ʈ������ �ؼ� ���� �ϳ��� 0�̸� 0�̳��´�. ??? ã�ƺ���
    {
        if (keyDown[key] == false)  //���� �����ӿ� ���ȴٰ� �ٲ��ִ� ��
        {
            keyDown[key] = true;
            return true;
        }
    }
    else
    {
        keyDown[key] = false;
    }

    return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
    //�ǽ�. ���� ������
    if (GetAsyncKeyState(key) & 0x8000)
    {
        keyUp[key] = false;
    }
    else
    {
        if (keyUp[key] == false)
        {
            keyUp[key] = true;
            return true;
        }
    }
    return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        return true;
    }
    return false;
}

bool KeyManager::IsStayKeyUp(int key)
{
    if (GetAsyncKeyState(key) & 0x0000)
    {
        return true;
    }
    return false;
}
