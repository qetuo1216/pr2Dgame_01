#include "stdafx.h"
#include "Animation.h"
#include "timer.h"


Animation::Animation(std::string name, int tag, bool state, float px, float py)
	:GameObject(name, tag, state, px, py)
{
	this->frameIdx = 0;
	this->frameDelay = 0.1;//0.2�ʵ��� �ִϸް� ����
	this->frameTimer = 0;//�ӵ����� ����

	this->aniIdx = 0;	//����� ���ϸ��� �迭 �ε���
}


Animation::~Animation()//ĳ���Ϳ� �������� �ִϸ��̼� Ŭ�������� ��ӹޱ⿡(frame) �θ��� ���⿡ �Ҹ��ڸ� �������
{
	//printf("�ִϸ� �Ҹ���\n");
	//�ε��� �ִϸ��̼� delete�ϱ�
	for (int i = 0; i < MAX_ANI; i++)
	{
		//1//splite����ü���� �����Ҵ��� �޸� ����
		for (int k = 0; k<frames[i].size();k++)
		{
			delete[] frames[i][k].argb;//bmp���� �ε��� �̹���(argb) ����
		}
		//2//stl������ ���� ����
		frames[i].clear();
	}
}

void Animation::draw()
{
	drawBmp(px, py, &frames[aniIdx][frameIdx]);
	
	//�ִϸ� �ð� ����
	frameTimer = frameTimer + getDelteTime();

	if (frameTimer>=frameDelay)//�ִϸ� ����� �ٲ���ϴ� �ð��� �Ǹ� ������ �ȴ�.
	{
		frameIdx++;

	if (frameIdx >= frames[aniIdx].size())//������ ������ ��� �� ó������
	{
		frameIdx = 0;
	}
	//�ִϸ� ��� �ٲ��� �˷��ִ� �̺�Ʈ
	OnAnimationEvent(aniIdx, frameIdx);
	frameTimer = 0;//�ִϸ� �ð� ����
	}
}

void Animation::addAniFrame(Sprite sprite,int aniId)
{
	frames[aniId].push_back(sprite);//�ִϸ��̼��� frames�� ����
}

void Animation::setFrameDelay(float delay)
{
	frameDelay = delay;
}

void Animation::play(int aniId)
{
	if(aniIdx!=aniId)//�ٸ� �Է��� ���� ���� ����
	{ 
		this->aniIdx = aniId;	//��¾ִϸ� �迭 ����
		this->frameIdx = 0;		//0�� �����Ӻ��� ����
	}
}

void Animation::OnAnimationEvent(int aniId, int aniFrame)
{

}