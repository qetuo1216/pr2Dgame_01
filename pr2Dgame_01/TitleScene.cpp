#include "stdafx.h"
#include "TitleScene.h"
#include "Title.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::init()
{
	//Ÿ��Ʋ �̹��� �ε�
	addGameObject(new Title(0, 0), 0);
}
