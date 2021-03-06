#pragma once
#include <vector>
#include "GameObject.h"
#include "ColPair.h"
#include <string>
//싱글톤사용하기
//게임오브젝트를 배열 형태로 밖에서 객체를 접근 못 만들게 한다.
#define MAX_LAYER 5
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
	vector<GameObject *> obj[MAX_LAYER];//레이어 설정 //0은 0번 레이어,1은 1번 레이어  

	//충돌쌍 저장 배열(stl Vector)
	vector<ColPair *> colPair;

public:
	//객체 가져오기 스테틱(정적) 메소드
	static gameObjectPool * instance();//pool이 null이면 객체를 만들고, 있으면 계속 사용한다.

	//게임 오브젝트 추가 및 제거 메소드
	void addGameObject(GameObject * o, int order);//obj배열에 들어감
	void delGameObject(GameObject * o);
	//추가된 객체 업데이트
	void update();

	//추가된 객체 draw
	void draw();

	//풀에 추가된 객체 충돌검사하기
	void checkCollision();
	void checkSameLayerCollision(int l);//1번 레이어 충돌 검사
	void checkDifLayerCollision(int lI,int lJ);//lI번 레이어와 lJ번 레이어 충돌 검사

	//삭제 표시된 게임오브젝트 제거하기
	void removeDeadObjs();
	
	//충돌쌍이 저장되었는지 판단하기
	bool checkInColPairs(GameObject *objI, GameObject *objJ, AABB *aabbI, AABB *aabbJ);
	
	//삭제되는 겍체가저장된 충돌쌍 제거하기
	void removeDeadColPair(GameObject *o);

	//충돌쌍 상태 리셋(충돌 끝으로 상태 변경)
	void resetColPairs();
	void removeUnColliedPairs();//충돌 종료 처리 함수

	//풀에 추가된 모든 객체 지우기
	void clear();

	//이름으로 게임 객체 찾기
	GameObject * find(string name);

	//추가된 객체 debugDraw
	void debugDraw();

};

