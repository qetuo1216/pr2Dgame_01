#pragma once
#include "Animation.h"
class Scythe : public Animation
{
private:
	//�̵� �ӵ�
	float speed;
public:
	Scythe(float px,float py);
	~Scythe();

	void init();
	void update();

	//���� �̵�
	float maxDist;	//�ִ� �����Ÿ�
	float moveDist;	//�̵��Ÿ� ����

};

