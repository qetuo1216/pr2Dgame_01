#pragma once
//�̱������ϱ�
//���ӿ�����Ʈ�� �迭 ���·� �ۿ��� ��ü�� ������� �Ѵ�.
class gameObjectPool
{
private:
	//�����ڿ� �Ҹ��ڸ� private�� �ֱ�
	gameObjectPool();//�⺻ ������
	virtual ~gameObjectPool();

	//�̱����� ������ ���� ������(��ü 1��)
	static gameObjectPool * pool;//
	
public:
	//��ü �������� ����ƽ(����) �޼ҵ�
	static gameObjectPool * instance();//pool�� null�̸� ��ü�� �����, ������ ��� ����Ѵ�.
};

