#pragma once
//ȸ������ �ʴ� �簢�� �ٿ���ڽ�(axis aligned bounding box) Ŭ���� ����
class AABB
{
private:
	//aabb��ǥ ũ��
	float x, y;//aabb���� ��� ��ǥ
	float width, height;//���� ���� ����

	//aabb ���� id
	int id;

public:
	//���� �Ҹ���
	AABB(float x,float y,float width,float height,int id);
	virtual ~AABB();

	//getter setter
	void getBB(float *x0, float *y0, float *x1, float *y1);
	void getBB(float &x0, float &y0, float &x1, float &y1);
	int getId();
	void setId(int id);
	//��Ÿ Ȱ�� �Լ�
	void translate(float dx, float dy);
	void debugDraw(unsigned char r, unsigned char g, unsigned char b);
};

