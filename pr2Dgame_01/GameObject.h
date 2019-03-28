#include <string>

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
	int state;			//상태
	//transform - 이동
	float px, py;		//위치이동
public:
	//생성자&소멸자
	GameObject(std::string name, int tag, int state,float px, float py);
	virtual ~GameObject();

	//기본활용 함수
	virtual void init();
	virtual void update();
	virtual void draw();

	//getter&setter
	//필요시에 만듬

	//기타
	//필요시에 만듬
};

