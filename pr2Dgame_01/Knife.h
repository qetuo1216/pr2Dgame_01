#pragma once
#include "Animation.h"
class Knife:public Animation
{
private:
	//�̵� �ӵ�
	float speed;

	//������ �����Ÿ�
	float maxDist;	//�ִ� �����Ÿ�
	float moveDist;	//�̵��Ÿ�
public:
	Knife(float px,float py);
	~Knife();
	
	//init �������̵�
	void init();
	void update();
};
