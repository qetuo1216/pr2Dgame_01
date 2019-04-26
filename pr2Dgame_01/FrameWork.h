#pragma once
#include "Scene.h"
class FrameWork	//Ư���� ��� �ʿ� ����.
{
private:
	//������&�Ҹ���
	FrameWork();
	virtual ~FrameWork();

	//��ü �����ϴ� ���� ������(��ü 1��)
	static FrameWork * frameWork;

	Scene * scene;//scene��ü ������ : ���� ������� ��
	Scene * nextScene;//��ȯ�� ���� �� ������
public:
	//�̱��� ��ü(�ν��Ͻ�) ��ȯ �޼ҵ�(static)
	static FrameWork * instance();//pool�� null�̸� ��ü�� �����, ������ ��� ����Ѵ�.

	//�����ӿ�ũ Ȱ�� �޼ҵ�
	void init(HWND hWnd,int width,int hight);
	void run();
	void exit();

	//�� �ε� ���
	void LoadScene(Scene * nextScene);
};

