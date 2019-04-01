#pragma once
#include "GameObject.h"
#include <vector>//그림의 개수를 자동으로 받는 배열을 사용
#include "bmp.h"

#define MAX_ANI 16
class Animation:public GameObject//게임 오브젝트를 상속
{
protected:
	//애니메 이미지들 저장하는 stl vector 사용
	std::vector<Sprite> frames[MAX_ANI];//16개의 애니메 사용 가능//백터를 배열형식으로 만들어 여러 애니메이션을 넣을 수 있다.
	int frameIdx; //출력할 애니메이션 프레임 인덱스

	float frameDelay; //애니메 장면 출력 시간
	float frameTimer; //애니메 시간 측정 변수
public:
	//생성자
	Animation(std::string name, int tag, bool state, float px, float py);
	~Animation();
	void draw();
	//플레이어 자체가 init과 update를 가질 예정

	//기타 활용함수
	void addAniFrame(Sprite sprite,int aniId);//애니메 프레임 추가 함수,aniId=애니메에 해당하는 배열에 애니메 추가
	void setFrameDelay(float delay); //애니메 속도 지정 함수
};

