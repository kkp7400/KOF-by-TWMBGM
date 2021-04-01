//Singleton.h

#pragma once
//#include"config.h"

template <typename T> //T�� ��� ������Ÿ�Կ� ���缭 ��ȭ��
class Singleton
{
protected:
	static T* instance;		// ���� ������ static�� �����Ϳ���(���α׷��� ������ ���� �Ҹ�x)	
	//static int* instance;
	//���⼭�� �� �� �ִ�  ����?
	Singleton() {};
	~Singleton() {};			//�����ڿ� �Ҹ��ڸ� �����̺��� ������ �ܺο��� �Ҵ��ϴ� ���� �Ұ���
public:
	static T* GetSingleton(); //t*�� ���� ������ �ٸ� Ŭ�������� �ּҸ� �̿��ؼ� ����ϱ� ���ؼ� 
	void ReleaseSingleton();
};

// ���� �ۿ��� �ʱ�ȭ -> static ��� ���� ������� �ؾ��ϴ� ����
template<typename T>						//��������� �߰�ȣ �ۿ��� �� �ʱ�ȭ�� �� ����Ѵ�
T* Singleton<T>::instance = nullptr;		

template<typename T>
inline T* Singleton<T>::GetSingleton()		//�̱����� ����ϰڽ��ϴ�. ���� �ν��Ͻ��� �ƹ��͵� ���ٸ� T�� keymanager������ �����´�
{
	if (instance == nullptr)
	{
		instance = new T;
	}
	return instance;
}

template<typename T>
inline void Singleton<T>::ReleaseSingleton()		//���� ������ ����� �����ϰ� nullptr�� �־��ش�.
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
