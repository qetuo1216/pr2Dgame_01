#pragma once
#include "GameObject.h"
#include <vector>//�׸��� ������ �ڵ����� �޴� �迭�� ���
#include "bmp.h"
class Animation:public GameObject//���� ������Ʈ�� ���
{
protected:
	//�ִϸ� �̹����� �����ϴ� stl vector ���
	std::vector<Sprite> frames;
public:
	//������
	Animation(std::string name, int tag, bool state, float px, float py);
	~Animation();
	void draw();
	//�÷��̾� ��ü�� init�� update�� ���� ����
};

