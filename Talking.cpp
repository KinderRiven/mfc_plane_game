#include "stdafx.h"
#include "Talking.h"
#include "resource.h"
#include "GameMessage.h"

Talking::Talking(int num)
{
	x = 0, y = 0;
	bmp.LoadBitmap(num + 11000);
}

Talking::~Talking()
{
}
void Talking::draw(CDC* pDC)
{
	width =  GameMessage::rect.Width();
	height = GameMessage::rect.Height();
	CDC mDC;
	mDC.CreateCompatibleDC(NULL);
	mDC.SelectObject(&bmp);
	pDC->TransparentBlt(x, y, width, height, &mDC, 0, 0, 1024, 768, RGB(0, 0, 0));
}