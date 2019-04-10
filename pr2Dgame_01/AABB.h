#pragma once
//회전되지 않는 사각형 바운딩박스(axis aligned bounding box) 클래스 구현
class AABB
{
private:
	//aabb좌표 크기
	float x, y;//aabb왼쪽 상단 좌표
	float width, height;//가로 세로 길이

	//aabb 구분 id
	int id;

public:
	//생성 소멸자
	AABB(float x,float y,float width,float height,int id);
	virtual ~AABB();

	//getter setter
	void getBB(float *x0, float *y0, float *x1, float *y1);
	void getBB(float &x0, float &y0, float &x1, float &y1);
	int getId();
	void setId(int id);
	//기타 활용 함수
	void translate(float dx, float dy);
	void debugDraw(unsigned char r, unsigned char g, unsigned char b);
};

