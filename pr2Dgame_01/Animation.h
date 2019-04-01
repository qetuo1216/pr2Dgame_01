#pragma once
#include "GameObject.h"
#include <vector>//�׸��� ������ �ڵ����� �޴� �迭�� ���
#include "bmp.h"

#define MAX_ANI 16
class Animation:public GameObject//���� ������Ʈ�� ���
{
protected:
	//�ִϸ� �̹����� �����ϴ� stl vector ���
	std::vector<Sprite> frames[MAX_ANI];//16���� �ִϸ� ��� ����//���͸� �迭�������� ����� ���� �ִϸ��̼��� ���� �� �ִ�.
	int frameIdx; //����� �ִϸ��̼� ������ �ε���

	float frameDelay; //�ִϸ� ��� ��� �ð�
	float frameTimer; //�ִϸ� �ð� ���� ����
public:
	//������
	Animation(std::string name, int tag, bool state, float px, float py);
	~Animation();
	void draw();
	//�÷��̾� ��ü�� init�� update�� ���� ����

	//��Ÿ Ȱ���Լ�
	void addAniFrame(Sprite sprite,int aniId);//�ִϸ� ������ �߰� �Լ�,aniId=�ִϸ޿� �ش��ϴ� �迭�� �ִϸ� �߰�
	void setFrameDelay(float delay); //�ִϸ� �ӵ� ���� �Լ�
};

