#include "stdafx.h"
#include "timer.h"

float prevTime =0;  //��������� ���� �ð�
float currTime =0;  //��������� ���� �ð�
float deltaTime=0;

////////Ÿ�̸�..������Ű��///////////
void initTimer()
{
    /////////DeltaTime(��ŸŸ��) - ��鰣�� �ɸ��� �ð�(��) ����/////
    prevTime = (float)GetTickCount() / 1000;  //��������� ���� �ð�
    currTime = (float)GetTickCount() / 1000;  //��������� ���� �ð�
    deltaTime;
}

void updateTimer()
{
    ////////���� �ð��� ������/////////////
    currTime = (float)GetTickCount() / 1000;
    deltaTime = currTime - prevTime;   //���� ��� �ð� - ���� ��� �ð�
    prevTime = currTime;              //���� ����� �ð��� ... ���� ����� ���� �ð��� ��
}

void exitTimer()
{
    //Ÿ�̸�..����� �ۼ� �ڵ� ����
}

////////��ŸŸ��..�������� �Լ�////////
float getDelteTime()
{
    return deltaTime;
}