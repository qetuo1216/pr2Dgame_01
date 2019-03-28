#include <string>

#pragma once
class GameObject	//�÷��̾�,����� ���� �ֻ��� ����
{
protected:		  //��ӹ��� �� ���� private��� �����

	//���ӿ�����Ʈ ���̵�
	static int ID;//ī��Ʈ
	int id;//���ӿ�����Ʈ�� �Ҵ���� ���̵�

	//�⺻ ������ -�̸�(string) �±�(int),����
	std::string name;	//�̸�		//const char * name;	//string ���� 	usingname space std;
	int tag;			//�±�				
	bool state;			//����
	//transform - �̵�
	float px, py;		//��ġ�̵�
public:
	//������&�Ҹ���
	GameObject(std::string name, int tag, bool state,float px, float py);
	virtual ~GameObject();

	//�⺻Ȱ�� �Լ�
	virtual void init();
	virtual void update();
	virtual void draw();

	//getter&setter
	//�ʿ�ÿ� ����

	//��Ÿ
	//�ʿ�ÿ� ����
};

