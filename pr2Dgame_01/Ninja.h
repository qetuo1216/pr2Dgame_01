#pragma once
#include "Animation.h"
#include "HUDBar.h"
class Ninja :public Animation
{
private:
	//�ִϸ��̼� ����
	enum State
	{
		drop = 0, idle, attack, hit, death
	};

	//�ִϸ��̼� ���� ����
	State state;
	int hp;//Ʈ�� ü��
	HUDBar * hpBar;//ü�¹� // �����ͷ� �ؾ� ���� ���� ����

	float dieDelay;//die�ִϸ��̼� ���� �ð�
public:
	Ninja(float px,float py);
	~Ninja();

	void init();
	void update();
	void aniTest();
};

