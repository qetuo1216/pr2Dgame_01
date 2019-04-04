#include "stdafx.h"
#include "gameObjectPool.h"

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

void gameObjectPool::addGameObject(GameObject * o)
{
	obj.push_back(o);	//객체 추가//크기가 늘어나면서 저장이 된다.
	o->init();			//객체 초기화
}

void gameObjectPool::update()
{
	for (int i = 0; i < obj.size(); i++)
	{
		obj[i]->update();
	}
}

void gameObjectPool::draw()
{
	for (int i = 0; i < obj.size(); i++)
	{
		obj[i]->draw();
	}
}
