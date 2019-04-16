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
	int aniIdx;	//����� �ִϸ� �迭 �ε���

	float frameDelay; //�ִϸ� ��� ��� �ð�
	float frameTimer; //�ִϸ� �ð� ���� ����

	//�¿� �ø� ���� �׽�Ʈ
	bool hFlip;//true�� �ø�
public:
	//������
	Animation(std::string name, int tag, bool state, float px, float py);
	~Animation();

	void draw();
	virtual void debugDraw();
	void translate(float dx, float dy);
	//�÷��̾� ��ü�� init�� update�� ���� ����

	//��Ÿ Ȱ���Լ�
	void addAniFrame(Sprite sprite,int aniId);//�ִϸ� ������ �߰� �Լ�,aniId=�ִϸ޿� �ش��ϴ� �迭�� �ִϸ� �߰�
	void setFrameDelay(float delay); //�ִϸ� �ӵ� ���� �Լ�
	void play(int aniId);//����� �ִϸ� �迭 �ε���

	//�ִϸ��̼� ��� ��ȯ �̺�Ʈ(�����Լ��� ����� �ڽ��� ����� �� �ֵ��� ��)
	virtual void OnAnimationEvent(int aniId,int aniFrame);
};

