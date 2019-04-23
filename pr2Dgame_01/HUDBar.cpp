#include "stdafx.h"
#include "HUDBar.h"
#include "graphic.h"

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
	readBmp("asset/Bar1.bmp", &bar);
	readBmp("asset/Bar1Bk.bmp", &barBk);
	//bar의 출력 길이값 테스트
	value = bar.width / 2;
}

void HUDBar::draw()
{
	//bar 이미지 그리기
	//drawBmp(px, py, &bar);
	for (int y = 0; y < bar.height; y++)
	{
		for (int x = 0; x < value; x++)
		{
			//x,y 위치에..픽셀을 출력함
			unsigned int pixel = bar.argb[y*bar.width + x];
			setPixel(px + x, py + y, pixel);
		}
	}
	//bar 태두리 출력
	drawBmp(px, py+50, &barBk);
}
