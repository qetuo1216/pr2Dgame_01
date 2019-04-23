#include "stdafx.h"
#include "HUDBar.h"


HUDBar::HUDBar(float px, float py) : GameObject("HUDBar",2,true,px,py)
{
}

HUDBar::~HUDBar()
{
	SafeDeleteArray(bar.argb);
	SafeDeleteArray(barBk.argb);
}

void HUDBar::init()
{
	//이미지 로드
	readBmp("asset/Bar1Bk.bmp", &bar);
	readBmp("asset/Bar1.bmp", &barBk);
}

void HUDBar::draw()
{
	//bar 이미지 그리기
	drawBmp(px, py, &bar);
	drawBmp(px, py+50, &barBk);
}
