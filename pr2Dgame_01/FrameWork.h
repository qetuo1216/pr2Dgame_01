#pragma once
class FrameWork	//Ư���� ��� �ʿ� ����.
{
private:
	//������&�Ҹ���
	FrameWork();
	virtual ~FrameWork();

	//��ü �����ϴ� ���� ������(��ü 1��)
	static FrameWork * frameWork;
public:
	//�̱��� ��ü(�ν��Ͻ�) ��ȯ �޼ҵ�(static)
	static FrameWork * instance();//pool�� null�̸� ��ü�� �����, ������ ��� ����Ѵ�.

	//�����ӿ�ũ Ȱ�� �޼ҵ�
	void init();
	void run();
	void exit();
};

