#include "stdafx.h"
#include "BackGround.h"
#include "timer.h"

BackGround::BackGround(float px, float py):SpliteObject("배경",0,true,px,py)//보통 0은 아군,1번은 적,2는 배경으로
{
}

BackGround::~BackGround()
{
}

void BackGround::init()
{
	//배경 이미지 로드하기
	readBMPRect("asset/배경.bmp", 0, 0, 4303, 224, &splite);

	//스크롤 속도 초기화
	speed = 100;//초당 100px로 이동
}

void BackGround::update()
{
	//스크롤 이동
	float d = speed * getDelteTime();
	translate(-d, 0);
	//px = px - d;
}
