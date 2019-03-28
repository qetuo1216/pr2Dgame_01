#include "stdafx.h"
#include "BackGround.h"

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
}
