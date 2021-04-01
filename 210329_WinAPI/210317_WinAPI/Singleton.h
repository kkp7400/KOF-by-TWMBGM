//Singleton.h

#pragma once
//#include"config.h"

template <typename T> //T는 모든 데이터타입에 맞춰서 변화함
class Singleton
{
protected:
	static T* instance;		// 전역 변수와 static은 데이터영역(프로그램이 끝날때 까지 소멸x)	
	//static int* instance;
	//여기서만 쓸 수 있는  변수?
	Singleton() {};
	~Singleton() {};			//생성자와 소멸자를 프라이빗에 넣으면 외부에서 할당하는 것이 불가능
public:
	static T* GetSingleton(); //t*을 쓰는 이유는 다른 클래스에서 주소를 이용해서 사용하기 위해서 
	void ReleaseSingleton();
};

// 영역 밖에서 초기화 -> static 멤버 변수 사용전에 해야하는 문법
template<typename T>						//멤버변수는 중괄호 밖에서 꼭 초기화를 해 줘야한다
T* Singleton<T>::instance = nullptr;		

template<typename T>
inline T* Singleton<T>::GetSingleton()		//싱글톤을 사용하겠습니다. 만약 인스턴스에 아무것도 없다면 T에 keymanager정보를 가져온다
{
	if (instance == nullptr)
	{
		instance = new T;
	}
	return instance;
}

template<typename T>
inline void Singleton<T>::ReleaseSingleton()		//모든게 끝나고 종료시 삭제하고 nullptr을 넣어준다.
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
