#include "stdafx.h"
#include "Input.h"

#define KEY_UP_REP   0  //키가 계속 놓인상태가 지속
#define KEY_DOWN     1  //키가 놓임==>눌림을 변함
#define KEY_DOWN_REP 2  //키가 계속 눌림상태를 지속
#define KEY_UP       3  //키가 눌림==>놓임으로 변함

int state[255];     //키보드의 모든 키상태를 저장하는 배열

					//키보드의 초기상태를 지정하는 함수
void initInput()
{
	for (int i = 0; i < 255; i++)
	{
		state[i] = KEY_UP_REP;  //게임이 시작할때 모든 키가 놓여있는 상태임
	}
}

void updateInput()
{
	for (int i = 1; i < 255; i++) //i는 배열 인덱스 이고 키번호
	{
		//(1)놓임==>눌림
		if ((state[i] == KEY_UP_REP || state[i] == KEY_UP) && GetAsyncKeyState(i) & 0X8000)
		{
			state[i] = KEY_DOWN; //키가 놓임 눌림으로 변경됨

								 //(2)눌림을 계속 반복
		}
		else if (state[i] == KEY_DOWN && GetAsyncKeyState(i) & 0X8000) {

			state[i] = KEY_DOWN_REP;

			//(3)키가 눌림 반복 ==> 놓임
		}
		else if ((state[i] == KEY_DOWN_REP || state[i] == KEY_DOWN) && GetAsyncKeyState(i) == 0) {

			state[i] = KEY_UP;

			//(4)키가 놓임이 반복됨
		}
		else if (state[i] == KEY_UP && GetAsyncKeyState(i) == 0) {
			state[i] = KEY_UP_REP;
		}
	}
}

//키가 놓음==>눌림으로 바뀌는 순간을 읽어오는 함수
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

//키가 눌림==>놓임으로 바뀌는 순간을 읽어오는 함수
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

//키가 계속 눌려있는지를 읽어오는 함수
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


