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
	//�̹��� �ε�
	readBmp("asset/Bar1.bmp", &bar);
	readBmp("asset/Bar1Bk.bmp", &barBk);
	//bar�� ��� ���̰� �׽�Ʈ
	value = bar.width / 2;
}

void HUDBar::draw()
{
	//bar �̹��� �׸���
	//drawBmp(px, py, &bar);
	for (int y = 0; y < bar.height; y++)
	{
		for (int x = 0; x < value; x++)
		{
			//x,y ��ġ��..�ȼ��� �����
			unsigned int pixel = bar.argb[y*bar.width + x];
			setPixel(px + x, py + y, pixel);
		}
	}
	//bar �µθ� ���
	drawBmp(px, py+50, &barBk);
}
