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
	//타이틀 이미지 로드
	addGameObject(new Title(0, 0), 0);
}
