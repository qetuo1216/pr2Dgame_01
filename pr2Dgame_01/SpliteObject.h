#pragma once
#include "GameObject.h"// ���� ������Ʈ ��ü�� ���
#include "bmp.h"
class SpliteObject :public GameObject// ���� ������Ʈ ��ü�� ���
{
protected:
	//bmp�� ��ü �߰�
	Sprite splite;//���� �̹��� ���� ����ü
public:
	//������&�Ҹ���
	SpliteObject(std::string name, int tag, bool state, float px, float py);
	virtual ~SpliteObject();

	//drow�Լ� �������̵�(���� ��ǰ������ init�� update�� ���)
	void draw();

};

