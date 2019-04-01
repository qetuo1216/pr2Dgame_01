#pragma once

#pragma pack(push, 1)   //구조체의 변수들을 ... 1 바이트씩 붙여라!!

/////////////bmp 파일 정보 구조체////////////
struct MyBITMAPFILEHEADER
{
	unsigned short bfType;		 //비트맵 파일이 정말 맞는지는 확인하는 내부 코드
	unsigned int   bfSize;		 //비트맵 파일의 크기 
	unsigned short bfReserved1;  //장래에..사용을 위한 예약 
	unsigned short bfReserved2;  //장래에..사용을 위한 예약
	unsigned int   bfOffBits;    //파일처음에서..그림 데이타가 있는 위치
};

//////////bmp 그림(이미지)정보 구조체///////////
struct MyBITMAPINFOHEADER
{
	unsigned int   biSize;           // 현재 구조체의 크기
	int            biWidth;          // 비트맵 이미지의 가로 크기
	int            biHeight;         // 비트맵 이미지의 세로 크기
	unsigned short biPlanes;         // 사용하는 색상판의 수
	unsigned short biBitCount;       // 픽셀 하나를 표현하는 비트 수
	unsigned int   biCompression;    // 압축 방식
	unsigned int   biSizeImage;      // 비트맵 이미지의 픽셀 데이터 크기
	int            biXPelsPerMeter;  // 그림의 가로 해상도(미터당 픽셀)
	int            biYPelsPerMeter;  // 그림의 세로 해상도(미터당 픽셀)
	unsigned int   biClrUsed;        // 색상 테이블에서 실제 사용되는 색상 수
	unsigned int   biClrImportant;   // 비트맵을 표현하기 위해 필요한 색상 인덱스 수
};

#pragma pack(pop)    //pack 설정을 꺼내라!!

struct Sprite	//그림을 저장할 구조체
{
	int width;  //스프라이트 이미지 가로 크기
	int height; //스프라이트 이미지 세로 크기

	int ax;		//앵커포인트 x좌표[객체의 px,py에 맞춰지는 이미지 위치]
	int ay;		//앵커포인트 y좌표

	unsigned int * argb;  //이미지 데이터 저장 
};

int readBmp(const char *fileName, Sprite *sprite);//전체 읽어오기
int readBMPRect(const char * filename, int x, int y, int width, int height, Sprite *sprite);
//일부분만 읽어오기
void drawBmp(float px, float py, Sprite *sprite);