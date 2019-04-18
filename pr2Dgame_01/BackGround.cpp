#include "stdafx.h"
#include "BackGround.h"
#include "timer.h"
#include "graphic.h"
#include "Barrel.h"
BackGround::BackGround(float px, float py):SpliteObject("배경",0,true,px,py)//보통 0은 아군,1번은 적,2는 배경으로
{
}

BackGround::~BackGround()
{
}

void BackGround::init()
{
	//배경 이미지 로드하기
	readBMPRect("asset/배경.bmp", 0, 0, 4303, 224, &sprite);

	//플레이어 이동을 막는 충돌체 추가. 0은 위,1은 아래, 2는 왼쪽,3은 오른쪽
	addCollider(new AABB(0, 140, 4304, 25, 0));//위로 이동 방지 충돌체
	addCollider(new AABB(208, 160, 35, 15, 0));//위로 이동 방지 충돌체(장애물)
	addCollider(new AABB(0, 220, 4304, 25, 1));//아래로 이동 방지 충돌체

	leftAABB = new AABB(-30, 140, 25, 105, 2);//왼쪽 충돌체
	addCollider(leftAABB);

	rightAABB = new AABB(getClientWidth()+15, 140, 25, 105, 3);//왼쪽 충돌체
	addCollider(rightAABB);
	
	//자식객체 추가하기
	addChildObject(new Barrel(200, 150), 2);

	//스크롤 속도 초기화
	speed = 100;//초당 100px로 이동
	scroll = true;//스크롤 중임
}
#define AA 0
void BackGround::update()
{
#if AA//조건부 컴파일
	if (scroll==true)
	{
		//스크롤 이동
		float d = speed * getDelteTime();

		//translate(-d, 0);//잠시 막아놓음
		//px = px - d;

		//배경 좌표 출력
		/*printf("화면의 크기 : %d\n", getClientWidth());
		printf("그림 가로 길이 : %d\n ", splite.width);*/
		//printf("%d\n", px);
		//배경 종료 판단하기
		int minPx = -(sprite.width - getClientWidth());
		//printf("%d", minPx);

		if (px > minPx)//배경 스크롤 중
		{
			translate(-d, 0);//배경 왼쪽 스크롤
			leftAABB->translate(d, 0);//왼쪽충돌체
			rightAABB->translate(d, 0);//왼쪽충돌체
		}
		else//스크롤 종료 
		{//px가 스크롤 중에 minPx보다 작아지는 경우
			int dx = minPx - px+1;

			translate(dx, 0);//가 minPx를 지난친 만큼 오른쪽으로 이동
			leftAABB->translate(-dx, 0);//왼쪽충돌체
			rightAABB->translate(-dx, 0);//왼쪽충돌체

			scroll = false;
		}
	}
#endif
}

void BackGround::onTriggerStay(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	//캐릭터 충돌체 바운딩박스 좌표 가져오기
	float a0, b0, a1, b1;
	otherAABB->getBB(a0, b0, a1, b1);

	//배경 충돌체 바운딩박스 좌표 가져오기
	float x0, y0, x1, y1;
	myAABB->getBB(x0, y0, x1, y1);

	if (OtherObj->GetName() == "나루토"&&otherAABB->getId() == 0 && myAABB->getId() == 0)
	{
		float dy = y1 - b0;
		OtherObj->translate(0, dy);
	}

	if (OtherObj->GetName() == "나루토"&&otherAABB->getId() == 0 && myAABB->getId() == 1)
	{
		float dy = b1 - y0;
		OtherObj->translate(0, -dy);
	}

	if (OtherObj->GetName() == "나루토"&&otherAABB->getId() == 0 && myAABB->getId() == 2)
	{
		//플레이어 이동거리
		float dx = x1 - a0;

		OtherObj->translate(dx, 0);
	}
	if (OtherObj->GetName() == "나루토"&&otherAABB->getId() == 0 && myAABB->getId() == 3)
	{
		//플레이어 이동거리
		float dx = a1-x0;

		OtherObj->translate(-dx, 0);
	}
}