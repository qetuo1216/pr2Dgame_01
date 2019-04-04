#pragma once
#include <vector>
#include "GameObject.h"
//싱글톤사용하기
//게임오브젝트를 배열 형태로 밖에서 객체를 접근 못 만들게 한다.
using namespace std;
class gameObjectPool
{
private:
	//생성자와 소멸자를 private로 넣기
	gameObjectPool();//기본 생성자
	virtual ~gameObjectPool();

	//싱글톤을 저장할 정적 포인터(객체 1개)
	static gameObjectPool * pool;//
	
	//게임 오브젝트를 저장하는 배열(stl vector) 자동 할당
	vector<GameObject *> obj;

public:
	//객체 가져오기 스테틱(정적) 메소드
	static gameObjectPool * instance();//pool이 null이면 객체를 만들고, 있으면 계속 사용한다.

	//게임 오브젝트 추가 메소드
	void addGameObject(GameObject * o);//obj배열에 들어감

	//추가된 객체 업데이트
	void update();

	//추가된 객체 draw
	void draw();
};

