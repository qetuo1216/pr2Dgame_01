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
	//transform - 이동
	float px, py;		//위치이동

	//충돌체 추가하기
	std::vector<AABB *> col;
	//충돌체 rgb 색상
	unsigned char colR, colG, colB;

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
	std::string GetName();
	std::vector<AABB *> getCollider();
	//기타
	void translate(float dx,float dy);//이동(translate) 함수

	void addGameObject(GameObject * o,int order);//객체 추가 메소드
	void delGameObject(GameObject * o);//객체 삭제 메소드
	
	//충돌체 추가 함수
	void addCollider(AABB *aabb);
	void setColColor(unsigned char r, unsigned char g, unsigned char b);//충돌체 출력 색상

	//충돌 이벤트 메소드
	virtual void onTriggerEnter(AABB* myAABB,GameObject *OtherObj,AABB* otherAABB);
};

