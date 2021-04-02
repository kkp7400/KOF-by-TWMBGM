#pragma once
#pragma once
#include "GameNode.h"
class Image;
class KofCommonFunc :public GameNode
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
	char command[4];
	char cinCommand;
	int commandTime;
	int elapedTime; // 100이 될 때마다 애니메이션 프레임을 1씩 증가
	int frame;	//애니메이션 프레임  0~8
	int maxFrame;
	int countCommand;
	bool canState;
	bool isCommand;
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

	void ResetCommand(char lastCharacter);

	void Move();
	void Attack();
};

