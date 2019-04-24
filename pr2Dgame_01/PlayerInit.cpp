#include "stdafx.h"
#include "Player.h"

void Player::init()
{
	//애니메이션 로드하기
	//Sprite sprite;
	//0번 idle
	for (int i = 0; i < 4; i++)
	{

		Sprite sprite;//※

		readBMPRect("asset/naruto.bmp", 2 + i * (42 + 2), 12, 42, 54, &sprite);//크기가 42*54, 우측상단이 2.12

		//충돌체 추가하기
		//sprite.col.push_back(new AABB(0, 0, 42, 54, 0));
		//sprite.col.clear();//이전 것 지우기

		addSpriteCollider(&sprite, new AABB(0, 50, 42, 5, 0), px, py);//※같은 좌표에 계속 넣으면 좌표가 어긋남, 충돌체를 이용할 때 이전 것을 없애야한다.
																	//이동 방지를 위한 충돌체 : 0번
		addSpriteCollider(&sprite, new AABB(0, 0, 42, 54, 1), px, py);//적 공격을 받기 위한 충돌체 : 1번
		addAniFrame(sprite, idle);//0번 배열에 집어넣음
		//frames.push_back(sprite);//애니메이션의 frames에 넣음
	}
	//sprite.col.clear();//추가된 충돌체 제거

	//1번 walk
	for (size_t i = 0; i < 6; i++)
	{
		Sprite sprite;
		readBMPRect("asset/naruto.bmp", 2 + i * (36 + 2), 80, 36, 56, &sprite);//크기가 42*54, 우측상단이 2.12

		addSpriteCollider(&sprite, new AABB(4, 50, 32, 5, 0), px, py);
		addSpriteCollider(&sprite, new AABB(4, 0, 32, 56, 1), px, py);

		addAniFrame(sprite, walk);//1번 배열에 집어넣음
	}

	//2번 run
	for (size_t i = 0; i < 6; i++)
	{
		Sprite sprite;

		readBMPRect("asset/naruto.bmp", 2 + i * (68 + 2), 150, 68, 45, &sprite);//크기가 42*54, 우측상단이 2.12


		//앵커포인트 조정하기
		sprite.ax = 10;//+는이미지가 왼쪽으로 이동,-는 오른쪽
		sprite.ay = -10;//+는이미지가 위으로 이동,-는 아래로

		addSpriteCollider(&sprite, new AABB(-15, 50, 65, 5, 0), px, py);
		addSpriteCollider(&sprite, new AABB(-15, 10, 65, 45, 1), px, py);
		addAniFrame(sprite, run);//2번 배열에 집어넣음
	}

	//3번 jump
	for (size_t i = 0; i < 2; i++)
	{
		Sprite sprite;

		readBMPRect("asset/naruto.bmp", 2 + i * (50 + 2), 332, 50, 51, &sprite);//크기가 42*54, 우측상단이 2.12

		//addSpriteCollider(&sprite, new AABB(0, 70, 50, 5, 0), px, py);
		//앵커포인트 조정하기
		//sprite.ay = 20;//+는이미지가 위으로 이동,-는 아래로

		addSpriteCollider(&sprite, new AABB(0, 0, 45, 49, 1), px, py);
		addAniFrame(sprite, jump);//3번 배열에 집어넣음
	}

	//4번 attack
	for (size_t i = 0; i < 3; i++)
	{
		Sprite sprite;

		readBMPRect("asset/naruto.bmp", 2 + i * (58 + 2), 584, 58, 49, &sprite);//크기가 42*54, 우측상단이 2.12

		//앵커포인트 조정하기
		sprite.ay = -5;//+는이미지가 위으로 이동,-는 아래로

		addSpriteCollider(&sprite, new AABB(0, 48, 58, 5, 0), px, py);
		addSpriteCollider(&sprite, new AABB(0, 0, 58, 48, 1), px, py);
		addAniFrame(sprite, attack);//4번 배열에 집어넣음
	}

	//5번 hit
	Sprite sprite;
	readBMPRect("asset/naruto.bmp", 2, 977, 42, 40, &sprite);//크기가 42*54, 우측상단이 2.12
	sprite.ax = 10;//+는이미지가 왼쪽으로 이동,-는 오른쪽

	//hit 충돌체 추가
	addSpriteCollider(&sprite, new AABB(-5, 0, 42, 40, 1), px, py);
	addAniFrame(sprite, hit);//5번 배열에 집어넣음

	//6번 airAttack
	for (size_t i = 0; i < 3; i++)
	{
		Sprite sprite;

		readBMPRect("asset/naruto.bmp", 2 + i * (57 + 2), 1416, 57, 56, &sprite);
		//addSpriteCollider(&sprite, new AABB(0, 0, 57, 56, 0), px, py);

		addAniFrame(sprite, airAttack);//4번 배열에 집어넣음
	}

	//death 이미지
	for (int i = 0; i < 3; i++)
	{
		Sprite sprite;

		readBMPRect("asset/naruto.bmp", 2 + i * (58 + 2), 1099, 58, 40, &sprite);
		sprite.ay = -20;
		addAniFrame(sprite, death);
	}
	//애니메 속도 지정하기
	setFrameDelay(0.15);

	//배경 이동 방지 충돌체 추가하기
	//addCollider(new AABB(0, 55, 40, 1, 0));

	//초기 애니메 변경하기
	state = idle;
	play(idle);

	//이동 속도 세팅
	walkSpeed = 50;
	runSpeed = 100;

	//점프 시간 변수 초기화
	//jumpDelay = 0.5;
	jumpTimer = 0;

	//점프 이동 및 가속도
	jumpMoveSpeed = 100;
	jumpUpSpeed = 200;
	jumpAcc = 400;//

	//hit 애니메이션 지속시간
	hitDelay = 0.5f;

	//hp 지정
	hp = 100;
	hpBar = new HUDBar(px-6,py-5);
	addChildObject(hpBar,2);
}