#pragma once
#include "Animation.h"
class Scythe : public Animation
{
private:
	//�̵� �ӵ�
	float speed;

	//���� �̵�
	float maxDist;	//�ִ� �����Ÿ�
	float moveDist;	//�̵��Ÿ� ����
	
	//���� ��ü ������ Ÿ�� �����ϱ�
	float lifeTime;

public:
	Scythe(float px,float py);
	~Scythe();

	void init();
	void update();

};

