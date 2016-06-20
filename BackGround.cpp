#include "stdafx.h"
#include "BackGround.h"
#include "resource.h"
#include "GameMessage.h"
#include "AllSpeed.h"

BackGround::BackGround(int num,int sp)
{
	speed = sp;				//背景移动速率
	dir_x = 0;
	dir_y = 1;
	bmp.LoadBitmap(num);	//加载背景位图
}
BackGround::BackGround(int num, int xx, int yy, int dx, int dy, int sp)
{
	speed = sp;
	bmp.LoadBitmap(num);
	x = xx; y = yy;
	dir_x = dx; dir_y = dy;
}
BackGround::~BackGround()
{
}
void BackGround::PaintPicture(CDC *pDC)
{
	width  = GameMessage::rect.Width();
	height = GameMessage::rect.Height();
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);	
	memDC.SelectObject(&bmp);
	if (y > GameMessage::rect.Height()) y = GameMessage::rect.Height() - height;
	pDC->StretchBlt(x, y, width, height, &memDC, 0, 0, 1024, 768, SRCCOPY);
	pDC->StretchBlt(x, y - height, width, height, &memDC, 0, 0, 1024, 768, SRCCOPY);
}
void BackGround::PaintPicture2(CDC *pDC)
{
	width = GameMessage::rect.Width();
	height = GameMessage::rect.Height();
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);
	pDC->TransparentBlt(x, y, width, height, &memDC, 0, 0, 1024, 768, RGB(255, 255, 255));
}