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
			GameObject * objI = obj[1][i];
			GameObject * objJ = obj[1][j];

			//objI와 objJ에서 충돌체 목록 가져오기
			std::vector<AABB *> colI = objI->getCollider();
			std::vector<AABB *> colJ = objJ->getCollider();

		}

		std::cout<<endl;
	}
		std::cout <<endl<< "--------------------" << endl;
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
