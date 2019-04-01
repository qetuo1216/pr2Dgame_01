#include "stdafx.h"
#include "Animation.h"
#include "timer.h"


Animation::Animation(std::string name, int tag, bool state, float px, float py)
	:GameObject(name, tag, state, px, py)
{
	this->frameIdx = 0;
	this->frameDelay = 0.1;//0.2�ʵ��� �ִϸް� ����
	this->frameTimer = 0;//�ӵ����� ����
}


Animation::~Animation()
{
}

void Animation::draw()
{
	drawBmp(px, py, &frames[0][frameIdx]);
	
	//�ִϸ� �ð� ����
	frameTimer = frameTimer + getDelteTime();

	if (frameTimer>=frameDelay)//�ִϸ� ����� �ٲ���ϴ� �ð��� �Ǹ� ������ �ȴ�.
	{
		frameIdx++;

	if (frameIdx >= frames[0].size())//������ ������ ��� �� ó������
	{
		frameIdx = 0;
	}
	frameTimer = 0;
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
