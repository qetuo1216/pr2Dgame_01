#include "stdafx.h"//�̸� ������ �� �ش��� �׻� �ٸ� �ش� ���� ���� (ù��)
#include "debug.h"



#pragma warning(disable:4996)



void START_DEBUG_CONSOLE()

{

	AllocConsole();                      //�����쿡�� �ܼ�â �����ϱ� �Լ�



	freopen("CONOUT$", "w", stdout); //printf �Ǵ� cout �� ���ؼ� ��µǴ� ǥ�� ���â���� ����

	freopen("CONIN$", "r", stdin);      //scanf_s �Ǵ� cin �� ���ؼ� �Է��� ���� �� �ִ� ǥ�� �Է� â���� ����

}



void STOP_DEBUG_CONSOLE()

{

	FreeConsole();                      //�����쿡�� �ܼ�â �����ϱ� �Լ�

}