#pragma once
//ȸ������ �ʴ� �簢�� �ٿ���ڽ�(axis aligned bounding box) Ŭ���� ����
class AABB
{
private:
	//aabb��ǥ ũ��
	float x, y;//aabb���� ��� ��ǥ
	float width, height;//���� ���� ����
public:
	//���� �Ҹ���
	AABB(float x,float y,float width,float height);
	virtual ~AABB();

	//getter setter

	//��Ÿ Ȱ�� �Լ�
	void translate(float dx, float dy);
	void debugDraw(unsigned char r, unsigned char g, unsigned char b);
};

