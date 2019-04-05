#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "timer.h"
#include "gameObjectPool.h"
#include "Knife.h"
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
		//sprite.ay = 20;//+는이미지가 위으로 이동,-는 아래로
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
	walkSpeed = 50;
	runSpeed = 100;

	//점프 시간 변수 초기화
	//jumpDelay = 0.5;
	jumpTimer = 0;
	
	//점프 이동 및 가속도
	jumpMoveSpeed = 100;
	jumpUpSpeed = 200;
	jumpAcc = 400;//
}
void Player::update()
{	
	//플레이어 애니메이션 스테이트 머신
	if (state == idle)
	{
		aniIdle();
	}
	else if (state == walk)
	{
		aniWalk();
		
	}
	else if (state == run)
	{
		aniRun();
		
	}
	else if (state == jump)
	{
		aniJump();
	}
	else if (state == attack)
	{
		aniAttack();
	}
}

void Player::aniIdle()
{
	//shift가 안눌리고 
	if (getKey(VK_LSHIFT) != true)
	{
		if (getKey(VK_LEFT) == true || getKey(VK_RIGHT) == true)//이동키 눌리면
		{
			state = walk;
			play(walk);
		}
	}
	else//shift가 눌리고
	{
		if (getKey(VK_LEFT) == true || getKey(VK_RIGHT) == true)//이동키 눌리면
		{
			state = run;	//run 상태로
			play(run);
		}
	}
	if (getKeyDown(VK_SPACE) == true)//스페이스 눌리면
	{
		state = jump;	//점프 상태로
		play(jump);

		//점프 속도 지정
		jumpTimer = 0;	//점프 측정시간 초기화
		jumpMoveSpeed = 0;//점프 이동 속도 초기화
		jumpStartY = py;//시작지점 초기화
	}
	if (getKeyDown('A') == true)//a키는 공격
	{
		state = attack;
		play(attack);
	}
}

void Player::aniWalk()
{
	float d = walkSpeed * getDelteTime();

	if (getKey(VK_RIGHT) == true)
	{
		hFlip = false;
		translate(d, 0);
	}
	if (getKey(VK_LEFT) == true)
	{
		hFlip = true;
		translate(-d, 0);

	}
	//이동 키가 놓이면 idle로
	if (getKey(VK_RIGHT) != true && getKey(VK_LEFT) != true)
	{
		state = idle;
		play(idle);
	}
	if (getKey(VK_LSHIFT))
	{
		if (getKey(VK_RIGHT) == true || getKey(VK_LEFT) == true)
		{
			state = run;
			play(run);
		}
	}
	if (getKeyDown(VK_SPACE) == true&& getKey(VK_LEFT) != true)//스페이스 눌리면
	{
		state = jump;	//점프 상태로
		play(jump);

		//점프 속도 지정
		jumpTimer = 0;
		jumpMoveSpeed = 50;
		jumpStartY = py;
	}
	if (getKeyDown('A') == true)//a키는 공격
	{
		state = attack;
		play(attack);
	}
}

void Player::aniRun()
{
	float d = runSpeed * getDelteTime();

	if (getKey(VK_LSHIFT) == true)//shift가 눌리고
	{
		if (getKey(VK_RIGHT) == true)//오른쪽 눌림
		{
			hFlip = false;
			translate(d, 0);
		}
		if (getKey(VK_LEFT) == true)//왼쪽 눌림
		{
			hFlip = true;
			translate(-d, 0);
		}

	}
	else//shift 놓임
	{
		state = idle;
		play(idle);
	}
	if (getKeyDown(VK_SPACE) == true && getKey(VK_LEFT) != true)//스페이스 눌리면
	{
		state = jump;	//점프 상태로
		play(jump);

		//점프 속도 지정
		jumpTimer = 0;
		jumpMoveSpeed = 100;
		jumpStartY = py;
	}
	if (getKeyDown('A') == true)//a키는 공격
	{
		state = attack;
		play(attack);
	}

}

void Player::aniJump()
{

	if (getKeyDown(VK_SPACE) != true)
	{
		//1.점프 시간 측정
		jumpTimer = jumpTimer + getDelteTime();

	
		//2.점프 이동시키기
		float upSpeed = jumpUpSpeed - jumpAcc * jumpTimer;//중력가속도로 계산 y축 이동

		float moveDist = jumpMoveSpeed * getDelteTime();//x축 이동 시간
		float upDist = upSpeed * getDelteTime();//위로 올라가기
	
		translate(moveDist, -upDist);
		
		//점프 후 원위치로 이동했는지 검사
		if (jumpStartY < py)
		{
			//점프 종료
			py = jumpStartY;

			//애니메이션 상태 종료
			state = idle;
			play(state);
		}
	}
		//2단 점프
		if (getKeyDown(VK_SPACE)==true)
		{
			jumpTimer = 0;//타이머를 리셋해서 가속도를 초기호
		}

		
}

void Player::aniAttack()
{
	
}

void Player::OnAnimationEvent(int aniId, int aniFrame)
{
	//printf("애니 %d, 애니 프레임 %d\n", aniId, aniFrame);
	if (aniId == attack&&aniFrame==0)
	{
		//수리검 투척(싱글톤 활용=하나의객체를 여러곳에서 사용)
		/*gameObjectPool * pool = gameObjectPool::instance();
		pool->addGameObject(new Knife(px+10, py+10));*/
		addGameObject(new Knife(px + 10, py + 10),1);
		//공격 애니메 종료
		state = idle;
		play(state);
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
