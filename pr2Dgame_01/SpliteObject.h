#pragma once
#include "GameObject.h"// 게임 오브젝트 객체를 상속
#include "bmp.h"
class SpliteObject :public GameObject// 게임 오브젝트 객체를 상속
{
protected:
	//bmp의 객체 추가
	Sprite splite;//게임 이미지 저장 구조체
public:
	//생성자&소멸자
	SpliteObject(std::string name, int tag, bool state, float px, float py);
	virtual ~SpliteObject();

	//drow함수 오버라이딩(배경과 물품은따로 init과 update를 사용)
	void draw();

};

