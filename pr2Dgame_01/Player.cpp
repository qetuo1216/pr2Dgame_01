#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "timer.h"
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
	//0번 idle
	for (int i = 0; i < 4; i++)
	{

	readBMPRect("asset/naruto.bmp", 2+i*(42+2), 12, 42, 54,&sprite);//크기가 42*54, 우측상단이 2.12
	addAniFrame(sprite,idle);//0번 배열에 집어넣음
	//frames.push_back(sprite);//애니메이션의 frames에 넣음
	}

	//1번 walk
	for (size_t i = 0; i < 6; i++)
	{
		readBMPRect("asset/naruto.bmp", 2 + i * (36 + 2), 80, 36, 56, &sprite);//크기가 42*54, 우측상단이 2.12
		addAniFrame(sprite, walk);//1번 배열에 집어넣음
	}

	//2번 run
	for (size_t i = 0; i < 6; i++)
	{
		readBMPRect("asset/naruto.bmp", 2 + i * (68 + 2), 150, 68, 45, &sprite);//크기가 42*54, 우측상단이 2.12

		//앵커포인트 조정하기
		sprite.ax = 10;//+는이미지가 왼쪽으로 이동,-는 오른쪽
		sprite.ay = -10;//+는이미지가 위으로 이동,-는 아래로

		addAniFrame(sprite, run);//2번 배열에 집어넣음
	}

	//3번 jump
	for (size_t i = 0; i < 2; i++)
	{
		readBMPRect("asset/naruto.bmp", 2 + i * (50 + 2), 332, 50, 51, &sprite);//크기가 42*54, 우측상단이 2.12

		//앵커포인트 조정하기
		sprite.ay = 20;//+는이미지가 위으로 이동,-는 아래로
		addAniFrame(sprite, jump);//3번 배열에 집어넣음
	}

	//4번 attack
	for (size_t i = 0; i < 3; i++)
	{
		readBMPRect("asset/naruto.bmp", 2 + i * (58 + 2), 584, 58, 48, &sprite);//크기가 42*54, 우측상단이 2.12


		//앵커포인트 조정하기
		sprite.ay = -5;//+는이미지가 위으로 이동,-는 아래로

		addAniFrame(sprite, attack);//4번 배열에 집어넣음
	}

	//5번 hit
	readBMPRect("asset/naruto.bmp", 2, 977, 42, 40, &sprite);//크기가 42*54, 우측상단이 2.12
	sprite.ax = 10;//+는이미지가 왼쪽으로 이동,-는 오른쪽
	addAniFrame(sprite, hit);//5번 배열에 집어넣음

	//애니메 속도 지정하기
	setFrameDelay(0.15);

	//초기 애니메 변경하기
	state = idle;
	play(idle);
	
	//이동 속도 세팅
	walkSpeed = 20;
}

void Player::update()
{
	if (state == idle)
	{
		//이동키 눌리면
		if (getKey(VK_LEFT) == true || getKey(VK_RIGHT) == true)
		{
			state = walk;
			play(walk);
		}
	}
	else if (state == walk)
	{
		float d = walkSpeed * getDelteTime();

		if (getKey(VK_RIGHT) == true)
		{
			translate(d, 0);
		}		
		if (getKey(VK_LEFT) == true)
		{
			translate(-d, 0);
		}
		
	}
}

void Player::aniTest()
{
	//'1'키는 IDLE
	//'2'키는 WALK
	if (getKey('1') == true)
	{
		play(idle);//0번 프레임부터 들어감
	}

	if (getKey('2') == true)
	{
		play(walk);
	}

	if (getKey('3') == true)
	{
		play(run);
	}

	if (getKey('4') == true)
	{
		play(jump);
	}

	if (getKey('5') == true)
	{
		play(attack);
	}

	if (getKey('6') == true)
	{
		play(hit);
	}
}
