#include "stdafx.h"//미리 컴파일 된 해더는 항상 다른 해더 파일 위에 (첫줄)
#include <stdio.h>
#include "bmp.h"
#include "graphic.h"

int readBmp(const char *fileName, Sprite *sprite)
{
	//[1]파일열기 - 바이너리파일 읽기로 열기
	FILE *stream;
	errno_t errno;

	errno = fopen_s(&stream, fileName, "rb");

	if (errno != 0)
	{
		printf("파일 열기 실패\n");
		return -1;
	}

	//[2]비트맵 파일읽기 - 파일정보 읽기
	MyBITMAPFILEHEADER bmpHeader;

	fread(&bmpHeader, sizeof(bmpHeader), 1, stream);

	///////////////////bmp 파일 정보 출력해 보기///////////////////
	printf("bfType    %x\n", bmpHeader.bfType);
	printf("bfSize    %d\n", bmpHeader.bfSize);
	printf("bfOffBits %d\n", bmpHeader.bfOffBits);

	if (bmpHeader.bfType != 0x4d42)  //올바른 bitmap 파일이 아님
	{
		printf("bitmap 파일이 아님\n");
		return -1;
	}

	//[3]비트맵 파일 읽기 - 이미지 정보 읽기
	MyBITMAPINFOHEADER bmpInfo;

	fread(&bmpInfo, sizeof(bmpInfo), 1, stream);

	printf("이미지 가로 크기 %d\n", bmpInfo.biWidth);
	printf("이미지 세로 크기 %d\n", bmpInfo.biHeight);
	printf("이미지 비트 카운트 %d\n", bmpInfo.biBitCount);

	if (bmpInfo.biBitCount != 32)  //32비트 형식 - ARGB 형식의 이미지만..이용
	{
		printf("비트맵 파일에..투명값(알파값)이 없음\n");
		return -1;
	}

	//[4]비트맵 파일 읽기 - 이미지 데이타 읽기
	sprite->width = bmpInfo.biWidth;   //이미지 가로 크기
	sprite->height = bmpInfo.biHeight;  //이미지 세로 크기

	/////이미지 저장 필요공간은 width * height * 4 바이트의 공간이 필요함
	sprite->argb = new unsigned int[sprite->width * sprite->height]; //이미지 데이타 저장 공간 할당

	fread(sprite->argb, sizeof(sprite->argb[0]), sprite->width*sprite->height, stream);

	//파일 닫기
	fclose(stream);

	return 0;  //비트맵 파일 읽기가..성공함
}

int readBMPRect(const char * filename, int x, int y, int width, int height, Sprite *sprite)
{

    //////////////비트맵 정보 구조체/////////////////
    MyBITMAPFILEHEADER fileHeader;   //비트맵 파일 정보 구조체
    MyBITMAPINFOHEADER infoHeader;  //이미지 정보 구조체

                                    //////////////BITMAP 파일 정보 읽기//////////////
    FILE * stream = NULL;
    errno_t errno;
    errno = fopen_s(&stream, filename, "rb");

    if (errno != 0)
    {
        printf("비트맵 파일 엵기 실패[%s]\n", filename);
        return -1;
    }

    ///////////비트맵 파일 구조체 읽어오기/////////////
    fread(&fileHeader, sizeof(fileHeader), 1, stream);

    //////////읽은 파일이 실제로 BMP 파일인지를 확인한다////////
    if (fileHeader.bfType != 0x4d42) //비트맵 파일이 아님
    {
        printf("비트맵 파일이 아님\n");
        return -1;
    }

    //////////이미지 정보 구조체 읽어오기///////////////
    fread(&infoHeader, sizeof(infoHeader), 1, stream);

    if (infoHeader.biBitCount != 32)
    {
        printf("픽셀의 비트갯수가 32가 아님\n");
        return -1;
    }


	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	////1) 읽어올 이미지만큼 건너뛰기
	int offset = y*infoHeader.biWidth * 4 +x* 4;
	fseek(stream, offset, SEEK_CUR);

	////2) 이미지 읽어오기
	int imgSize = width * height * 4;
	unsigned int * argb = new unsigned int[imgSize];//이미지 사이즈

	//fread(argb, 4, width, stream);//4바이트씩 읽어옴(1줄)
	
	int gap = (infoHeader.biWidth - width)*4;//한 줄 읽고 나머지 데이터 건너띄기 

	for (int i = 0; i < height; i++)
	{
		fread(argb+width*i, 4, width, stream);
		fseek(stream, gap, SEEK_CUR);
	}
	//fread(argb+width, 4, width, stream);

	fclose(stream);

	////3) 구조체 포인터에 읽어온 이미지 전달.
	sprite->width = width;
	sprite->height = height;
	sprite->argb = argb;
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////

    return 0;
	/*

    fseek(stream, fileHeader.bfOffBits, SEEK_SET);  //이미지가 저장된 위치로..이동함

                                                    ////////이미지 데이타 (argb)를 저장할 메모리 할당//////
    sprite->width = width;
    sprite->height = height;
    sprite->argb = new unsigned int[width * height];

    ///////파일에서 원하는 영역을 읽기 위한 변수 계산/////////////////////////
    int lineSize = width * 4;                  //로드할 이미지 한줄 데이타 크기 (1칸이 4바이트)
    int stride = infoHeader.biWidth * 4;      //파일의 이미지 한줄 데이타 크기

	//1) 읽어올 이미지만큼 건너뛰기
    int offset = y * stride + x * 4;	     //파일의 이미지 로드 시작 위치 (1칸이 4byte)
    int lineGap = stride - lineSize;          //파일과 이미지 한줄 데이타 크기의 차

    fseek(stream, offset, SEEK_CUR);          //데이타 읽기 시작 위치로 이동

    for (int k = 0; k < height; k++)
    {
        fread(&sprite->argb[k*width], lineSize, 1, stream); //파일에서 한줄을 읽는다.
        fseek(stream, lineGap, SEEK_CUR);                //파일에서 읽고 남은 줄을 건너뛰고..다음 읽을 위치로 이동한다
    }

    fclose(stream);
*/
}

void drawBmp(float px, float py, Sprite *sprite)
{
	///////////이미지 출력하기////////////
	for (int y = 0; y < sprite->height; y++)
	{
		for (int x = 0; x < sprite->width; x++)
		{
			//x,y 위치에..픽셀을 출력함
			unsigned int pixel = sprite->argb[y*sprite->width + x];
			setPixel(px + x, py + y, pixel);
		}
	}
}

