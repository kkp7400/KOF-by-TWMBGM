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
	int elapedTime; // 100이 될 때마다 애니메이션 프레임을 1씩 증가
	int frame;	//애니메이션 프레임  0~8
	int maxFrame;
	//커맨드를 위한 변수
	int countCommand;//현재 몇번째 커맨드인지 판별
	char command[4];//입력받은 커맨드를 저장
	char cinCommand;//누른 키 값을 위 command배열에 저장하기 위한 변수
	int commandTime;//커맨드 제한시간
	//여기까지
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

