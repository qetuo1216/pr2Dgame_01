#pragma once
#include "SpliteObject.h"
class BackGround : public SpliteObject//SpliteObject�� ���
{
private:
	//��� ��ũ�� �ӵ�
	float speed;
public:
	//������&�Ҹ���
	BackGround(float px, float py);
	~BackGround();

	//init,update �������̵�
	void init();
	void update();//�̵��ӵ� ����Ͽ� �̵���Ŵ
};

