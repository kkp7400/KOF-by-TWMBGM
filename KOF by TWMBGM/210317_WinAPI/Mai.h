#pragma once
#include "GameNode.h"
class Image;
class Mai :public GameNode
{
private:
	Image* img_Idle;
	Image* img_Front_walk;
	Image* img_Back_walk;
	Image* img_foot_Strong_Attack;
	Image* img_foot_Weak_Attack;
	Image* img_fist_Strong_Attack;
	Image* img_fist_Weak_Attack;	
	Image* img_Skill_1;
	FPOINT pos;	
	int elapedTime; // 100�� �� ������ �ִϸ��̼� �������� 1�� ����
	int frame;	//�ִϸ��̼� ������  0~8
	int maxFrame;
	//Ŀ�ǵ带 ���� ����
	int countCommand;//���� ���° Ŀ�ǵ����� �Ǻ�
	char command[4];//�Է¹��� Ŀ�ǵ带 ����
	char cinCommand;//���� Ű ���� �� command�迭�� �����ϱ� ���� ����
	int commandTime;//Ŀ�ǵ� ���ѽð�
	//�������
	bool canState;
	RECT hitCol;
	RECT atkCol;
	enum State
	{
		Idle,
		Front,
		Back,
		Hit,
		Foot_Strong_Attack,
		Foot_Weak_Attack,
		Fist_Strong_Attack,
		Fist_Weak_Attack,		
		Skill_1
	};
	State state;
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void ResetCommand();

	void Move();
	void Attack();
	void UpdateHitCol();
	void UpdateAtkCol();
	
};

