#include "stdafx.h"
#include "Title.h"
#include "bmp.h"
#include "FrameWork.h"
#include "GameScene.h"
#include "Input.h"
Title::Title(float px,float py):SpliteObject("Ÿ��Ʋ", 2, true, px, py)//���� 0�� �Ʊ�,1���� ��,2�� �������
{
}


Title::~Title()
{
}

void Title::init()
{
	//Ÿ��Ʋ �̹��� �ε� �ϱ�
	readBMPRect("asset/Ÿ��Ʋ.bmp",0,0,800,224, &sprite);
	
}

void Title::update()
{
	//�� ��ȯ �׽�Ʈ
	if (getKeyDown(VK_RETURN) == true)
	{
		FrameWork::instance()->LoadScene(new GameScene);
	}
}
