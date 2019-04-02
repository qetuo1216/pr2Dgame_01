#pragma once
#include "Animation.h"
//�ִϸ��̼� ���� enum
enum State { idle = 0, walk, run, jump, attack, hit };
class Player : public Animation
{
private:
	State state;//�ִϸ��̼� ���� enum

	//�ӵ�
	float walkSpeed;
	float runSpeed;

	//���� ���� �ð� ����
	float jumpDelay;//���� ���� �ð�
	float jumpTimer;//���� �ð� ���� ����

public:
	Player(float px,float py);
	~Player();

	void init();
	void update();

	//�ִϸ� ���� �Լ�
	void aniIdle();
	void aniWalk();
	void aniRun();
	void aniJump();
	void aniAttack();

	//�ִϸ� ��ȯ�̺�Ʈ �������̵�
	void OnAnimationEvent(int aniId, int aniFrame);
	//
	void aniTest();
};

