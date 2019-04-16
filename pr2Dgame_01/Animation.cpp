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
	
	this->hFlip = false;
}


Animation::~Animation()//캐릭터와 나이프가 애니메이션 클래스에서 상속받기에(frame) 부모인 여기에 소멸자를 사용하자
{
	//printf("애니메 소멸자\n");
	//로드한 애니메이션 delete하기
	for (int i = 0; i < MAX_ANI; i++)
	{
		//1//splite구조체에서 동적할당한 메모리 해제
		for (int k = 0; k<frames[i].size();k++)
		{
			//delete[] frames[i][k].argb;//bmp에서 로드한 이미지(argb) 삭제
			SafeDeleteArray(frames[i][k].argb);
		}
		//2//stl백터의 공간 삭제
		frames[i].clear();
	}
}

void Animation::draw()
{
	if (hFlip == true)
	{
		drawBmpFlip(px, py, &frames[aniIdx][frameIdx]);
	}
	else
	{
		drawBmp(px, py, &frames[aniIdx][frameIdx]);
	}
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

void Animation::debugDraw()
{
	//충돌체 추가
	//frames[aniIdx][frameIdx].col;
	std::vector<AABB *> *ptrCol = &frames[aniIdx][frameIdx].col;
	for (int i = 0; i < ptrCol->size(); i++)
	{
		(*ptrCol)[i]->debugDraw(colR,colG,colB);
		
	}
}

std::vector<AABB*> Animation::getCollider()
{
	return frames[aniIdx][frameIdx].col;
}
void Animation::translate(float dx, float dy)
{
	//게임 오브젝트 이동
	px = px + dx;
	py = py + dy;

	//게임 스플라이트 추가된 충돌체들 이동
	for (int j = 0; j < MAX_ANI; j++)//모든 애니메이션 반복
	{
		for (int i = 0; i < frames[j].size(); i++)//모든 스플라이트 반복
		{
			std::vector<AABB *> *ptrCol = &frames[j][i].col;
			
			for (int k = 0; k < ptrCol->size(); k++)
			{
				(*ptrCol)[k]->translate(dx, dy);
			}
		}
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
