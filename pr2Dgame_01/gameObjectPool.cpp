#include "stdafx.h"
#include "gameObjectPool.h"
#include <iostream>
//static 포인터 만들기
gameObjectPool * gameObjectPool::pool=NULL;

//생성자&소멸자
gameObjectPool::gameObjectPool()
{
}


gameObjectPool::~gameObjectPool()
{
}

//인스턴스 반환 메소드(객체가 있는지 검사)
gameObjectPool * gameObjectPool::instance()
{
	if (gameObjectPool::pool == NULL)
	{
		gameObjectPool::pool = new gameObjectPool();//같은 클래스 안의 private는 접근 가능
	}

	return gameObjectPool::pool;

}

void gameObjectPool::addGameObject(GameObject * o, int order)//order은 레이어 번호
{


		obj[order].push_back(o);	//객체 추가//크기가 늘어나면서 저장이 된다.
		o->init();			//객체 초기화
	
}

void gameObjectPool::delGameObject(GameObject * o)
{
	//객체 안에서 바로 delete하는 것은 코드가 안전하지 못한다.
	int id = o->getId();
	for (int l = 0; l < MAX_LAYER; l++)
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			if (obj[l][i]->getId() == id)//일치하는 아이디를 찾음
			{
				//1//객체 delete
				delete obj[l][i];//또는 delete o; //소멸자가 실행
				//2//stl vector에서 저장공간 삭제
				obj[l].erase(obj[l].begin() + i);
			}
		}
	}
}


void gameObjectPool::update()
{
	for (int l = 0; l < MAX_LAYER; l++)
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			obj[l][i]->update();
		}
	}
}

void gameObjectPool::draw()
{
	for (int l = 0; l < MAX_LAYER; l++)//l은 레이어 번호
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			if (obj[l][i]->getState() == true)//상태 검사
			{
				obj[l][i]->draw();
			}
		}
	}
	
}

void gameObjectPool::checkCollision()//충돌 검사 업데이트가 끝나면 한다.
{
	//1//1번 레이어 충돌검사하기
	for (int j = 0; j < obj[1].size(); j++)
	{
		for (int i = 0; i < j; i++)
		{
			//printf("%s", obj[1][i]->GetName);;
			//if (i < j)//중복된 순서쌍 제거
			//std::cout << "[" << obj[1][i]->GetName() << ", " << obj[1][j]->GetName() << "]";
			//충돌체 생성
			GameObject * objI = obj[1][i];
			GameObject * objJ = obj[1][j];

			//objI와 objJ에서 충돌체 목록 가져오기
			std::vector<AABB *> colI = objI->getCollider();
			std::vector<AABB *> colJ = objJ->getCollider();

			//충돌체 (AABB)간의 충돌검사
			for (int ii = 0; ii < colI.size(); ii++)
			{
				for (int jj = 0; jj < colJ.size(); jj++)
				{
					AABB * aabbI = colI[ii];//objI에서 가져온 ii번째 AABB//출력된 사각형
					AABB * aabbJ = colJ[jj];//objI에서 가져온 ii번째 AABB

					//aabbI와 aabbJ가 사각형 단위로 충돌했는지 검사
					//cout << objI->GetName() << ", " << objJ->GetName() << endl;
					
					//사각형의 좌표를 가져와서 선 단위로 가져온다.(좌측상단,우측하단)
					float x0, y0, x1, y1;//aabbI의 꼭지점 좌표
					float a0, b0, a1, b1;//aabbJ의 꼭지점 좌표

					aabbI->getBB(x0, y0, x1, y1);
					aabbJ->getBB(a0, b0, a1, b1);

					if (x1 >= a0 && x0 <= a1 && y1 >= b0 && b1 >= y0)
					{
						/*cout << "충돌 정보----------------------" << endl;
						cout << "첫번째 객체 :" << objI->GetName() << endl;
						cout << "첫번째 객체 aabb의 ID:" << aabbI->getId() << endl;

						cout << "두번째 객체 :" << objJ->GetName() << endl;
						cout << "첫번째 객체 aabb의 ID:" << aabbJ->getId() << endl;*/
						//충돌 정보(이벤트) 전달
						//1//objI에게 자신의 충돌체 aabbI와 게임오브젝트 ObjJ와 충돌하고, objJ의 aabbJ와 충돌이 발생
						objI->onTriggerEnter(aabbI, objJ, aabbJ);

						//2//objJ에게 자신의 충돌체 aabbJ와 게임오브젝트 ObjI와 충돌하고, objI의 aabbI와 충돌이 발생
						objJ->onTriggerEnter(aabbJ, objI, aabbI);
					}
				}
			}
		}

		
	}
		//std::cout <<endl<< "--------------------" << endl;
}


void gameObjectPool::debugDraw()
{
	for (int l = 0; l < MAX_LAYER; l++)//l은 레이어 번호
	{
		for (int i = 0; i < obj[l].size(); i++)
		{
			//if (obj[l][i]->getState() == true)//상태 검사
			{
				obj[l][i]->debugDraw();
			}
		}
	}
}
