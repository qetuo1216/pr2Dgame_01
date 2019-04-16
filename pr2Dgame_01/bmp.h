#pragma once

#include <vector>
#include "AABB.h"

#pragma pack(push, 1)   //����ü�� �������� ... 1 ����Ʈ�� �ٿ���!!

/////////////bmp ���� ���� ����ü////////////
struct MyBITMAPFILEHEADER
{
	unsigned short bfType;		 //��Ʈ�� ������ ���� �´����� Ȯ���ϴ� ���� �ڵ�
	unsigned int   bfSize;		 //��Ʈ�� ������ ũ�� 
	unsigned short bfReserved1;  //�巡��..����� ���� ���� 
	unsigned short bfReserved2;  //�巡��..����� ���� ����
	unsigned int   bfOffBits;    //����ó������..�׸� ����Ÿ�� �ִ� ��ġ
};

//////////bmp �׸�(�̹���)���� ����ü///////////
struct MyBITMAPINFOHEADER
{
	unsigned int   biSize;           // ���� ����ü�� ũ��
	int            biWidth;          // ��Ʈ�� �̹����� ���� ũ��
	int            biHeight;         // ��Ʈ�� �̹����� ���� ũ��
	unsigned short biPlanes;         // ����ϴ� �������� ��
	unsigned short biBitCount;       // �ȼ� �ϳ��� ǥ���ϴ� ��Ʈ ��
	unsigned int   biCompression;    // ���� ���
	unsigned int   biSizeImage;      // ��Ʈ�� �̹����� �ȼ� ������ ũ��
	int            biXPelsPerMeter;  // �׸��� ���� �ػ�(���ʹ� �ȼ�)
	int            biYPelsPerMeter;  // �׸��� ���� �ػ�(���ʹ� �ȼ�)
	unsigned int   biClrUsed;        // ���� ���̺��� ���� ���Ǵ� ���� ��
	unsigned int   biClrImportant;   // ��Ʈ���� ǥ���ϱ� ���� �ʿ��� ���� �ε��� ��
};

#pragma pack(pop)    //pack ������ ������!!

struct Sprite	//�׸��� ������ ����ü
{
	int width;  //��������Ʈ �̹��� ���� ũ��
	int height; //��������Ʈ �̹��� ���� ũ��

	int ax;		//��Ŀ����Ʈ x��ǥ[��ü�� px,py�� �������� �̹��� ��ġ]
	int ay;		//��Ŀ����Ʈ y��ǥ
	//[����] �ø��� ax,ay�� ���� �����ؾ��� �� �� �ִ�.

	//�׸����� �浹ü�� ���� �����Ѵ�. std::vctor
	std::vector<AABB *> col;

	unsigned int * argb;  //�̹��� ������ ���� 
};

//���ö���Ʈ �浹ü �Լ� �߰�
void addSpriteCollider(Sprite * sprite, AABB * aabb, float px, float py);

int readBmp(const char *fileName, Sprite *sprite);//��ü �о����
int readBMPRect(const char * filename, int x, int y, int width, int height, Sprite *sprite);
//�Ϻκи� �о����
void drawBmp(float px, float py, Sprite *sprite);
void drawBmpFlip(float px, float py, Sprite *sprite);