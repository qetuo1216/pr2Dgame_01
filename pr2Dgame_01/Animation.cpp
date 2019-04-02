#include "stdafx.h"
#include "Animation.h"
#include "timer.h"


Animation::Animation(std::string name, int tag, bool state, float px, float py)
	:GameObject(name, tag, state, px, py)
{
	this->frameIdx = 0;
	this->frameDelay = 0.1;//0.2초동안 애니메가 보임
	this->frameTimer = 0;//속도측정 변수

	this->aniIdx = 0;	//출력할 에니매의 배열 인덱스
}


Animation::~Animation()
{
}

void Animation::draw()
{
	drawBmp(px, py, &frames[aniIdx][frameIdx]);
	
	//애니메 시간 측정
	frameTimer = frameTimer + getDelteTime();

	if (frameTimer>=frameDelay)//애니메 장면을 바꿔야하는 시간이 되면 실행이 된다.
	{
		frameIdx++;

	if (frameIdx >= frames[aniIdx].size())//마지막 프레임 출력 후 처음부터
	{
		frameIdx = 0;
	}
	//애니메 장면 바꿈을 알려주는 이벤트
	OnAnimationEvent(aniIdx, frameIdx);
	frameTimer = 0;//애니메 시간 리셋
	}
}

void Animation::addAniFrame(Sprite sprite,int aniId)
{
	frames[aniId].push_back(sprite);//애니메이션의 frames에 넣음
}

void Animation::setFrameDelay(float delay)
{
	frameDelay = delay;
}

void Animation::play(int aniId)
{
	if(aniIdx!=aniId)//다른 입력이 들어올 때만 변경
	{ 
		this->aniIdx = aniId;	//출력애니메 배열 변경
		this->frameIdx = 0;		//0번 프레임부터 시작
	}
}

void Animation::OnAnimationEvent(int aniId, int aniFrame)
{

}
