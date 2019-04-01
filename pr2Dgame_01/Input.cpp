#include "stdafx.h"
#include "Input.h"

#define KEY_UP_REP   0  //Ű�� ��� ���λ��°� ����
#define KEY_DOWN     1  //Ű�� ����==>������ ����
#define KEY_DOWN_REP 2  //Ű�� ��� �������¸� ����
#define KEY_UP       3  //Ű�� ����==>�������� ����

int state[255];     //Ű������ ��� Ű���¸� �����ϴ� �迭

					//Ű������ �ʱ���¸� �����ϴ� �Լ�
void initInput()
{
	for (int i = 0; i < 255; i++)
	{
		state[i] = KEY_UP_REP;  //������ �����Ҷ� ��� Ű�� �����ִ� ������
	}
}

void updateInput()
{
	for (int i = 1; i < 255; i++) //i�� �迭 �ε��� �̰� Ű��ȣ
	{
		//(1)����==>����
		if ((state[i] == KEY_UP_REP || state[i] == KEY_UP) && GetAsyncKeyState(i) & 0X8000)
		{
			state[i] = KEY_DOWN; //Ű�� ���� �������� �����

								 //(2)������ ��� �ݺ�
		}
		else if (state[i] == KEY_DOWN && GetAsyncKeyState(i) & 0X8000) {

			state[i] = KEY_DOWN_REP;

			//(3)Ű�� ���� �ݺ� ==> ����
		}
		else if ((state[i] == KEY_DOWN_REP || state[i] == KEY_DOWN) && GetAsyncKeyState(i) == 0) {

			state[i] = KEY_UP;

			//(4)Ű�� ������ �ݺ���
		}
		else if (state[i] == KEY_UP && GetAsyncKeyState(i) == 0) {
			state[i] = KEY_UP_REP;
		}
	}
}

//Ű�� ����==>�������� �ٲ�� ������ �о���� �Լ�
bool getKeyDown(int keycode)
{
	if (state[keycode] == KEY_DOWN)
	{
		return true;
	}
	else {
		return false;
	}
}

//Ű�� ����==>�������� �ٲ�� ������ �о���� �Լ�
bool getKeyUp(int keycode)
{
	if (state[keycode] == KEY_UP)
	{
		return true;
	}
	else {
		return false;
	}
}

//Ű�� ��� �����ִ����� �о���� �Լ�
bool getKey(int keycode)
{
	if (state[keycode] == KEY_DOWN || state[keycode] == KEY_DOWN_REP)
	{
		return true;
	}
	else {
		return false;
	}
}


