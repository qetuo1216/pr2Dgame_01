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
	AABB();
	virtual ~AABB();

	//getter setter

	//��Ÿ Ȱ�� �Լ�
};

