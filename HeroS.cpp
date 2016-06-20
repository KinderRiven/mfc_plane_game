#include "stdafx.h"
#include "HeroS.h"
#include "resource.h"
#include "GameNature.h"
HeroS::HeroS(int lv)
{
	width  = 124;
	height =  97;
	bmp.LoadBitmap(lv + 2000);
}

HeroS::~HeroS()
{

}
void HeroS::draw(int xx,int yy,CDC* pDC)
{
	CDC mDC;
	mDC.CreateCompatibleDC(NULL);
	mDC.SelectObject(&bmp);
	pDC->TransparentBlt(xx, yy, 60, 40, &mDC, 0, 0, width, height, RGB(238, 243, 250));
}