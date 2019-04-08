#pragma once
//회전되지 않는 사각형 바운딩박스(axis aligned bounding box) 클래스 구현
class AABB
{
private:
	//aabb좌표 크기
	float x, y;//aabb왼쪽 상단 좌표
	float width, height;//가로 세로 길이
public:
	//생성 소멸자
	AABB();
	virtual ~AABB();

	//getter setter

	//기타 활용 함수
};

