#include "stdafx.h"
#include "Title.h"
#include "bmp.h"

Title::Title(float px,float py):SpliteObject("타이틀", 2, true, px, py)//보통 0은 아군,1번은 적,2는 배경으로
{
}


Title::~Title()
{
}

void Title::init()
{
	//타이틀 이미지 로드 하기
	readBMPRect("asset/타이틀.bmp",0,0,800,224, &sprite);
	
}
