#include "stdafx.h"
#include <Windows.h>
#include <math.h>
#include "graphic.h"
#ifndef SafeDeleteArray
    #define SafeDeleteArray(_X_) if ( (_X_) != NULL) { delete[] (_X_);  (_X_) = NULL;}
#endif

static HWND outHWnd     = NULL;  //�׷��� ��� ������ �ڵ�

static int  clientX      = 0;   //�׷��� ��� ����(�簢�� ����)�� ���� x-��ǥ
static int  clientY      = 0;   //�׷��� ��� ����(�簢�� ����)�� ���� y-��ǥ
static int  clientWidth  = 0;   //�׷��� ��� ����(�簢�� ����)�� ���� ����(�ʺ�)
static int  clientHeight = 0;   //�׷��� ��� ����(�簢�� ����)�� ���� ����(����)

static unsigned int * backBuffer = NULL; //�׷��� ��� �����

/////////////////////�׷��� ��� �ʱ�ȭ �Լ�//////////////////////
void initGraphic(HWND hWnd, int x, int y, int width, int height)
{
    if (hWnd == NULL)  //�׷��� ���..�ڵ��� NULL �̸� �ܼ���������..�ڵ��� ���ؼ� ����Ѵ�.
    {
        outHWnd = GetConsoleHwnd();
    }
    else {
        outHWnd = hWnd;
    }

    /////////////�׷��� ��� ����(�簢�� ����)�� ��ġ�� ũ�⸦ ����(static)������ �����Ѵ�///////////////
    clientX = x;
    clientY = y;
    clientWidth  = width;
    clientHeight = height;

    ////////////����۸� ���� �����Ѵ�.//////////////
    backBuffer = new unsigned int[clientWidth * clientHeight];
}

int getClientWidth()      //�׷��� ��� �簢���� ���� ���̸� ��ȯ��
{
    return clientWidth;
}

int getClientHeight()     //�׷��� ��� �簢���� ���� ���̸� ��ȯ��
{
    return clientHeight;
}

///////////////////r, g, b ������ ����۸� �ʱ�ȭ �ϴ� �Լ�////////////////////////////////////////////
void clear(unsigned char r, unsigned char g, unsigned char b)     //r, g, b ������..����۸� �ʱ�ȭ��
{
    unsigned int color = (r << 16) | (g << 8) | (b << 0);

    for (int j = 0; j < clientHeight; j++)
    {
        for (int i = 0; i < clientWidth; i++)
        {
            backBuffer[j*clientWidth + i] = color;
        }
    }
}

/////////////////r, g, b ���� x, y ��ġ�� ����ϴ� �Լ�/////////////////////
void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) //x,y ��ġ�� r, g, b �������
{
    if (0 <= x && x < clientWidth && 0 <= y && y < clientHeight)
    {
        unsigned int color = (r << 16) | (g << 8) | (b << 0);
        backBuffer[y*clientWidth + x] = color;
    }
}

/////////////////color(a, r, g, b)�� x, y ��ġ�� ����ϴ� �Լ�////////////////////
void setPixel(int x, int y, unsigned int color) //x, y ��ġ�� r, g, b �������(���İ� ����)
{
    if (0 <= x && x < clientWidth && 0 <= y && y < clientHeight)
    {
        ///////////////��»����� a, r, g, b/////////////
        unsigned char a = (color >> 24) & 0xff;
        unsigned char r = (color >> 16) & 0xff;
        unsigned char g = (color >>  8) & 0xff;
        unsigned char b = (color >>  0) & 0xff;

        /////////////������(����ۿ� ��µ�)�� r, g, b//////
        unsigned char R, G, B;
        getPixel(x, y, &R, &G, &B);

        //���ĺ��� ���Ŀ� ���ؼ� ������..�̹��� �ȼ��� ���´�.
        r = ((255 - a)*R + a * r) / 255;
        g = ((255 - a)*G + a * g) / 255;
        b = ((255 - a)*B + a * b) / 255;

        //���ĺ�����..������ ..����ۿ� ����Ѵ�
        setPixel(x, y, r, g, b);
    }
}

////////////////////////����ۿ��� �̹���µ� ����(r, g, b)�� �����´�////////////////////
void getPixel(int x, int y, unsigned char &r, unsigned char &g, unsigned char &b)  //x,y ��ġ����..�̹� ��µ� r, g, b���� ������
{
    if (0 <= x && x < clientWidth && 0 <= y && y < clientHeight)
    {
        unsigned int color = backBuffer[y*clientWidth + x];

        r = (color >> 16) & 0xff;
        g = (color >>  8) & 0xff;
        b = (color >>  0) & 0xff;
    }
    else {
        r = g = b = 0;
    }
}

void getPixel(int x, int y, unsigned char *r, unsigned char *g, unsigned char *b)  //x,y ��ġ����..�̹� ��µ� r, g, b���� ������
{
    getPixel(x, y, *r, *g, *b);
}

//////////////////////�������� (x0, y0)�̰� ������ (x1, y1)�� ������ r, g, b �������� ����ۿ� ����Ѵ�/////////
void drawLine(int x0, int y0, int x1, int y1, unsigned char r, unsigned char g, unsigned char b) //(x0, y0)���� (x1, y1)�� �մ� �����׸��� - r, g, b �� ����
{
    //////////////////Bresenham Algorithms ���� ���� �׸���///////////////
    ////[���� �׸��� ���� ����Ʈ] https://gist.github.com/bert/1085538
    int dx = abs(x1 - x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy) / 2, e2;

    for (;;) 
    {
        setPixel(x0, y0, r, g, b);

        if (x0 == x1 && y0 == y1) break;

        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}
//////////////////////////////�߽��� (cx, cy)�̰� �������� radius �� ���� r, g, b�������� ����ۿ� �׸���///////////////
void drawCircle(int cx, int cy, int radius, unsigned char r, unsigned char g, unsigned b) //�߽���(cx, cy)�̰� �������� radius�� �� �׸��� - r, g, b �� ����
{
    /***********************************************************************
    int x = 0, y = 0;

    for (x = 0; x <= y; x++)
    {
        y = (int)(sqrt(radius*radius - x * x) + 0.5); // y �� ��ǥ�� ����Ѵ�.

        setPixel(cx + x, cy + y, r, g, b); 
        setPixel(cx + x, cy - y, r, g, b);
        setPixel(cx - x, cy + y, r, g, b);
        setPixel(cx - x, cy - y, r, g, b);
        setPixel(cx + y, cy + x, r, g, b);
        setPixel(cx + y, cy - x, r, g, b);
        setPixel(cx - y, cy + x, r, g, b);
        setPixel(cx - y, cy - x, r, g, b);
    }
    ***************************************************************************/
    ////[���׸��� ���� ����Ʈ] https://gist.github.com/bert/1085538
    int x = -radius, y = 0, err = 2 - 2 * radius; /* II. Quadrant */

    do {
        setPixel(cx - x, cy + y, r, g, b); /*   I. Quadrant */
        setPixel(cx - y, cy - x, r, g, b); /*  II. Quadrant */
        setPixel(cx + x, cy - y, r, g, b); /* III. Quadrant */
        setPixel(cx + y, cy + x, r, g, b); /*  IV. Quadrant */
        radius = err;
        if (radius >  x) err += ++x * 2 + 1; /* e_xy+e_x > 0 */
        if (radius <= y) err += ++y * 2 + 1; /* e_xy+e_y < 0 */

    } while (x < 0);
}

///////////////////// (x0, y0)�� ���� ��� �������̰�, (x1, y1)������ �ϴ� �������� �簢���� r, g, b�������� ����ۿ� �׸���///////////
void drawRect(int x0, int y0, int x1, int y1, unsigned char r, unsigned char g, unsigned char b) //���ʻ�ܲ����� (x0, y0)�� �����ʲ����� (x1, y1)����  �簢�� �׸��� - r, g, b �� ����
{
    drawLine(x0, y0, x1, y0, r, g, b);
    drawLine(x0, y1, x1, y1, r, g, b);

    drawLine(x0, y0, x0, y1, r, g, b);
    drawLine(x1, y0, x1, y1, r, g, b);
}

///////////////////�������.. �׷��� ����Ÿ(����ۿ� ��µ� �ȼ�)�� �ش� ������..������ ����Ѵ�//////////////
void render() //�������...�׷��� ����Ÿ�� ȭ��(������ ����)�� ���
{
    HDC hDC, hMemDC;
    HBITMAP  hBmp;
    void   * bmpBuffer;
    int size;

    hDC    = GetDC(outHWnd);
    hMemDC = CreateCompatibleDC(hDC);
    size   = clientWidth * clientHeight * 4;

    BITMAPINFO bi;
    ZeroMemory(&bi, sizeof(BITMAPINFO));

    bi.bmiHeader.biSize     = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth    =  clientWidth;
    bi.bmiHeader.biHeight   = -clientHeight;
    bi.bmiHeader.biPlanes   = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
   
    hBmp = CreateDIBSection(hDC, &bi, DIB_RGB_COLORS, &bmpBuffer, NULL, 0);
    SelectObject(hMemDC, hBmp);

    CopyMemory(bmpBuffer, backBuffer, size);

    BitBlt(hDC, clientX, clientY, clientWidth, clientHeight, hMemDC, 0, 0, SRCCOPY);

    DeleteObject(hBmp);
    DeleteDC(hMemDC);
    DeleteObject(hDC);
}

///////////////�׷��� ��� ���� �Լ�////////////////////////////////
void exitGraphic()
{
    SafeDeleteArray(backBuffer);
}

#ifdef UNICODE

HWND GetConsoleHwnd()
{
    #define MY_BUFSIZE 1024 // Buffer size for console window titles.
	HWND hwndFound;         // This is what is returned to the caller.
	WCHAR pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
										 // WindowTitle.
	WCHAR pszOldWindowTitle[MY_BUFSIZE];  // Contains original
										  // WindowTitle.

										  // Fetch current window title.

	GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
	// Format a "unique" NewWindowTitle.

	wsprintf(pszNewWindowTitle, L"%d/%d", GetTickCount(), GetCurrentProcessId());
	// Change current window title.

	SetConsoleTitle(pszNewWindowTitle);

	// Ensure window title has been updated.
	Sleep(40);

	// Look for NewWindowTitle.
	hwndFound = FindWindow(NULL, pszNewWindowTitle);

	// Restore original window title.
	SetConsoleTitle(pszOldWindowTitle);

	return(hwndFound);
}

#else

HWND GetConsoleHwnd()
{
    #define MY_BUFSIZE 1024 // Buffer size for console window titles.
	HWND hwndFound;         // This is what is returned to the caller.
	CHAR pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
										 // WindowTitle.
	CHAR pszOldWindowTitle[MY_BUFSIZE];  // Contains original
										  // WindowTitle.

										  // Fetch current window title.

	GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
	// Format a "unique" NewWindowTitle.

	wsprintf(pszNewWindowTitle, "%d/%d", GetTickCount(), GetCurrentProcessId());
	// Change current window title.

	SetConsoleTitle(pszNewWindowTitle);

	// Ensure window title has been updated.
	Sleep(40);

	// Look for NewWindowTitle.
	hwndFound = FindWindow(NULL, pszNewWindowTitle);

	// Restore original window title.
	SetConsoleTitle(pszOldWindowTitle);

	return(hwndFound);
}

#endif
