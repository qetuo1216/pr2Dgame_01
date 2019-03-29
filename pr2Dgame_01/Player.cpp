#include "stdafx.h"
#include "Player.h"


Player::Player(float px, float py):Animation("나루토",0,true,px,py)
{
}


Player::~Player()
{
}

void Player::init()
{
	//애니메이션 로드하기
	Sprite sprite;
	readBMPRect("asset/naruto.bmp", 2, 12, 42, 54,&sprite);//크기가 42*54, 우측상단이 2.12
	frames.push_back(sprite);//애니메이션의 frames에 넣음
}
