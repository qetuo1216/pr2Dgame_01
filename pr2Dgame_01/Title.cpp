#include "stdafx.h"
#include "Title.h"
#include "bmp.h"

Title::Title(float px,float py):SpliteObject("Ÿ��Ʋ", 2, true, px, py)//���� 0�� �Ʊ�,1���� ��,2�� �������
{
}


Title::~Title()
{
}

void Title::init()
{
	//Ÿ��Ʋ �̹��� �ε� �ϱ�
	readBmp("asset/Ÿ��Ʋ.bmp", &sprite);
	
}
