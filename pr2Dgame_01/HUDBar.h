#pragma once
#include "GameObject.h"
#include "bmp.h"
class HUDBar : public GameObject
{
private:
	Sprite bar;//�� �̹���
	Sprite barBk;//�� �µθ� �̹���

	//bar�� ��� ����
	int value;
public:
	HUDBar(float px,float py);
	~HUDBar();

	void init();
	void draw();

	//bar ���̰� ����
	void setValue(float v);//���� ���� 0~1����
};

