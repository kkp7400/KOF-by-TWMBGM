#include "config.h"
#include "KeyManager.h"



HRESULT KeyManager::Init()
{
    keyUp.set();        //1로 세팅
    keyDown.reset();    //0으로 세팅

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
        GetAsyncKeyState(VK_...) <- 현재 키가 어떤 상태인지 (하드웨어 속도로=빠르게)알려줌
        
        함수 호출 시점에 가상키(VK_...)가 어떤 상태인지 확인
        1. 0x0000(16진수) -> 이전 프레임에 누른 적이 없고 호출시점에도 눌려있지 않음
        2. 0x0001 -> 이전 프레임에 누른적이 있고 호출시점에는 눌려있지 않음
        3. 0x8000 -> 이전 프레임에 누른적이 없고 호출시점에는 눌려있는 상태
        0x8 이진수로 바꾸면-> 1000
        4. 0x8001 -> 이전 프레임에 누른적이 있고 호출시점에도 눌려있는 상태 

    */

    if (GetAsyncKeyState(key) & 0x8000) // & 비트연산자 ->비트연산을 해서 둘중 하나라도 0이면 0이나온다. ??? 찾아보기
    {
        if (keyDown[key] == false)  //이전 프레임에 눌렸다고 바꿔주는 중
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
    //실습. 직접 만들어보자
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
