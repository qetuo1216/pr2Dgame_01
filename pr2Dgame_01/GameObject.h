#include <string>
#define SafeDeleteArray(X) if(X != NULL) {	delete[] X;	X = NULL;}
#include <vector>
#include "AABB.h"
#pragma once
class GameObject	//플레이어,배경을 위한 최상위 계층
{
protected:		  //상속받을 때 보통 private대신 사용함

	//게임오브젝트 아이디
	static int ID;//카운트
	int id;//게임오브젝트에 할당받은 아이디

	//기본 데이터 -이름(string) 태그(int),상태
	std::string name;	//이름		//const char * name;	//string 사용시 	usingname space std;
	int tag;			//태그				
	bool state;			//상태
	bool alive;			//이동/충돌체에 의해 지워져야 하는지를 판단하는 변수
	//transform - 이동
	float px, py;		//위치이동
	//충돌체 추가하기
	std::vector<AABB *> col;
	//충돌체 rgb 색상
	unsigned char colR, colG, colB;

	//자식 게임오브젝트 추가하기(상속과 무관하다)
	//게임 오브젝트들을 서로 연결 같이 움직이도록 한다(계층구조로) 부모계층 이 이동할때 자식계층이 따라 움직일 수 있도록
	std::vector<GameObject *> child;
	GameObject * parentObj;//자식 게임오브젝트인 경우 부모객체의 포인터를 저장함

public:
	//생성자&소멸자
	GameObject(std::string name, int tag, bool state,float px, float py);
	virtual ~GameObject();

	//기본활용 함수
	virtual void init();
	virtual void update();
	virtual void draw();
	//충돌체 그리기함수 추가
	virtual void debugDraw();


	//getter&setter
	//필요시에 만듬
	int getId();
	int getTag();

	bool getState();
	void setState(bool state);

	bool getAlive();
	void setAlive(bool alive);

	float getPx();//x좌표 게터
	float getPy();//y좌표 게터

	std::string GetName();
	virtual std::vector<AABB *> getCollider();
	//기타
	virtual void translate(float dx,float dy);//이동(translate) 함수

	void addGameObject(GameObject * o,int order);//객체 추가 메소드
	void delGameObject(GameObject * o);//객체 삭제 메소드
	
	//충돌체 추가 함수
	void addCollider(AABB *aabb);
	void setColColor(unsigned char r, unsigned char g, unsigned char b);//충돌체 출력 색상

	//자식객체 추가 함수
	void addChildObject(GameObject *o,int order);//자식 게임오브젝트 추가하기,레이어 포함
	void delChildObject(GameObject * o);//자식 객체 삭제 메소드

	//충돌 이벤트 메소드
	virtual void onTriggerEnter(AABB* myAABB,GameObject *OtherObj,AABB* otherAABB);//처음 충돌
	virtual void onTriggerStay(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//반복
	virtual void onTriggerExit(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//충돌 종료

	//피해를 주고받는 메소드
	virtual void DoDamage(GameObject *fromObj, GameObject *toObj, AABB* fromAABB,int damage);
};

