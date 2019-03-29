#pragma once
#include "GameObject.h"
#include <vector>//그림의 개수를 자동으로 받는 배열을 사용
#include "bmp.h"
class Animation:public GameObject//게임 오브젝트를 상속
{
protected:
	//애니메 이미지들 저장하는 stl vector 사용
	std::vector<Sprite> frames;
public:
	//생성자
	Animation(std::string name, int tag, bool state, float px, float py);
	~Animation();
	void draw();
	//플레이어 자체가 init과 update를 가질 예정
};

