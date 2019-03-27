#pragma once

#include <Windows.h>

void initGraphic(HWND hWnd, int x, int y, int width, int height);  //�׷��� ��� �ʱ�ȭ
void exitGraphic();                                                //�׷��� ��� ���� 

void clear(unsigned char r, unsigned char g, unsigned char b);     //r, g, b ������..����۸� �ʱ�ȭ��

void render(); //�������...�׷��� ����Ÿ�� ȭ��(������ ����)�� ���

void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b); //x,y ��ġ�� r, g, b �������
void setPixel(int x, int y, unsigned int color); //x, y ��ġ�� r, g, b �������(���İ� ����)

void getPixel(int x, int y, unsigned char &r, unsigned char &g, unsigned char &b);  //x,y ��ġ����..�̹� ��µ� r, g, b���� ������
void getPixel(int x, int y, unsigned char *r, unsigned char *g, unsigned char *b);  //x,y ��ġ����..�̹� ��µ� r, g, b���� ������

void drawLine(int x0, int y0, int x1, int y1, unsigned char r, unsigned char g, unsigned char b); //(x0, y0)���� (x1, y1)�� �մ� �����׸��� - r, g, b �� ����
void drawCircle(int cx, int cy, int radius, unsigned char r, unsigned char g, unsigned b);        //�߽���(cx, cy)�̰� �������� radius�� �� �׸��� - r, g, b �� ����
void drawRect(int x0, int y0, int x1, int y1, unsigned char r, unsigned char g, unsigned char b); //���ʻ�ܲ����� (x0, y0)�� �����ʲ����� (x1, y1)����  �簢�� �׸��� - r, g, b �� ����

int getClientWidth();      //�׷��� ��� �簢���� ���� ���̸� ��ȯ��
int getClientHeight();     //�׷��� ��� �簢���� ���� ���̸� ��ȯ��

HWND GetConsoleHwnd();