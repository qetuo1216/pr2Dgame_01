#include "stdafx.h"//�̸� ������ �� �ش��� �׻� �ٸ� �ش� ���� ���� (ù��)
#include <stdio.h>
#include "bmp.h"
#include "graphic.h"

int readBmp(const char *fileName, Sprite *sprite)
{
	//[1]���Ͽ��� - ���̳ʸ����� �б�� ����
	FILE *stream;
	errno_t errno;

	errno = fopen_s(&stream, fileName, "rb");

	if (errno != 0)
	{
		printf("���� ���� ����\n");
		return -1;
	}

	//[2]��Ʈ�� �����б� - �������� �б�
	MyBITMAPFILEHEADER bmpHeader;

	fread(&bmpHeader, sizeof(bmpHeader), 1, stream);

	///////////////////bmp ���� ���� ����� ����///////////////////
	printf("bfType    %x\n", bmpHeader.bfType);
	printf("bfSize    %d\n", bmpHeader.bfSize);
	printf("bfOffBits %d\n", bmpHeader.bfOffBits);

	if (bmpHeader.bfType != 0x4d42)  //�ùٸ� bitmap ������ �ƴ�
	{
		printf("bitmap ������ �ƴ�\n");
		return -1;
	}

	//[3]��Ʈ�� ���� �б� - �̹��� ���� �б�
	MyBITMAPINFOHEADER bmpInfo;

	fread(&bmpInfo, sizeof(bmpInfo), 1, stream);

	printf("�̹��� ���� ũ�� %d\n", bmpInfo.biWidth);
	printf("�̹��� ���� ũ�� %d\n", bmpInfo.biHeight);
	printf("�̹��� ��Ʈ ī��Ʈ %d\n", bmpInfo.biBitCount);

	if (bmpInfo.biBitCount != 32)  //32��Ʈ ���� - ARGB ������ �̹�����..�̿�
	{
		printf("��Ʈ�� ���Ͽ�..����(���İ�)�� ����\n");
		return -1;
	}

	//[4]��Ʈ�� ���� �б� - �̹��� ����Ÿ �б�
	sprite->width = bmpInfo.biWidth;   //�̹��� ���� ũ��
	sprite->height = bmpInfo.biHeight;  //�̹��� ���� ũ��

	/////�̹��� ���� �ʿ������ width * height * 4 ����Ʈ�� ������ �ʿ���
	sprite->argb = new unsigned int[sprite->width * sprite->height]; //�̹��� ����Ÿ ���� ���� �Ҵ�

	fread(sprite->argb, sizeof(sprite->argb[0]), sprite->width*sprite->height, stream);

	//���� �ݱ�
	fclose(stream);

	return 0;  //��Ʈ�� ���� �бⰡ..������
}

int readBMPRect(const char * filename, int x, int y, int width, int height, Sprite *sprite)
{

    //////////////��Ʈ�� ���� ����ü/////////////////
    MyBITMAPFILEHEADER fileHeader;   //��Ʈ�� ���� ���� ����ü
    MyBITMAPINFOHEADER infoHeader;  //�̹��� ���� ����ü

                                    //////////////BITMAP ���� ���� �б�//////////////
    FILE * stream = NULL;
    errno_t errno;
    errno = fopen_s(&stream, filename, "rb");

    if (errno != 0)
    {
        printf("��Ʈ�� ���� ���� ����[%s]\n", filename);
        return -1;
    }

    ///////////��Ʈ�� ���� ����ü �о����/////////////
    fread(&fileHeader, sizeof(fileHeader), 1, stream);

    //////////���� ������ ������ BMP ���������� Ȯ���Ѵ�////////
    if (fileHeader.bfType != 0x4d42) //��Ʈ�� ������ �ƴ�
    {
        printf("��Ʈ�� ������ �ƴ�\n");
        return -1;
    }

    //////////�̹��� ���� ����ü �о����///////////////
    fread(&infoHeader, sizeof(infoHeader), 1, stream);

    if (infoHeader.biBitCount != 32)
    {
        printf("�ȼ��� ��Ʈ������ 32�� �ƴ�\n");
        return -1;
    }


	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	////1) �о�� �̹�����ŭ �ǳʶٱ�
	int offset = y*infoHeader.biWidth * 4 +x* 4;
	fseek(stream, offset, SEEK_CUR);

	////2) �̹��� �о����
	int imgSize = width * height * 4;
	unsigned int * argb = new unsigned int[imgSize];//�̹��� ������

	//fread(argb, 4, width, stream);//4����Ʈ�� �о��(1��)
	
	int gap = (infoHeader.biWidth - width)*4;//�� �� �а� ������ ������ �ǳʶ�� 

	for (int i = 0; i < height; i++)
	{
		fread(argb+width*i, 4, width, stream);
		fseek(stream, gap, SEEK_CUR);
	}
	//fread(argb+width, 4, width, stream);

	fclose(stream);

	////3) ����ü �����Ϳ� �о�� �̹��� ����.
	sprite->width = width;
	sprite->height = height;
	sprite->argb = argb;
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////

    return 0;
	/*

    fseek(stream, fileHeader.bfOffBits, SEEK_SET);  //�̹����� ����� ��ġ��..�̵���

                                                    ////////�̹��� ����Ÿ (argb)�� ������ �޸� �Ҵ�//////
    sprite->width = width;
    sprite->height = height;
    sprite->argb = new unsigned int[width * height];

    ///////���Ͽ��� ���ϴ� ������ �б� ���� ���� ���/////////////////////////
    int lineSize = width * 4;                  //�ε��� �̹��� ���� ����Ÿ ũ�� (1ĭ�� 4����Ʈ)
    int stride = infoHeader.biWidth * 4;      //������ �̹��� ���� ����Ÿ ũ��

	//1) �о�� �̹�����ŭ �ǳʶٱ�
    int offset = y * stride + x * 4;	     //������ �̹��� �ε� ���� ��ġ (1ĭ�� 4byte)
    int lineGap = stride - lineSize;          //���ϰ� �̹��� ���� ����Ÿ ũ���� ��

    fseek(stream, offset, SEEK_CUR);          //����Ÿ �б� ���� ��ġ�� �̵�

    for (int k = 0; k < height; k++)
    {
        fread(&sprite->argb[k*width], lineSize, 1, stream); //���Ͽ��� ������ �д´�.
        fseek(stream, lineGap, SEEK_CUR);                //���Ͽ��� �а� ���� ���� �ǳʶٰ�..���� ���� ��ġ�� �̵��Ѵ�
    }

    fclose(stream);
*/
}

void drawBmp(float px, float py, Sprite *sprite)
{
	///////////�̹��� ����ϱ�////////////
	for (int y = 0; y < sprite->height; y++)
	{
		for (int x = 0; x < sprite->width; x++)
		{
			//x,y ��ġ��..�ȼ��� �����
			unsigned int pixel = sprite->argb[y*sprite->width + x];
			setPixel(px + x, py + y, pixel);
		}
	}
}

