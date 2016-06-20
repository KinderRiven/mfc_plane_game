#include "stdafx.h"
#include "Things.h"
#include "GameMessage.h"
Things::Things(int lv,int xx,int yy) //位置，种类
{
	x = xx; y = yy;
	Lv = lv;
	width   = 60;
	height  = 60;
	is_dead = false; //物品存在
	bmp.LoadBitmap(lv + 6000);
	//物品属性
	if (lv == 1) value = 0;
	if (lv == 2) value = 1000;
	if (lv == 3) value = 1500;
	if (lv == 4) value = 500;
	speed = 10;
	dir_y = 1;
	int t = rand() % 3;
	dir_x = t - 1; //随机方向
}
Things::~Things()
{
}
void Things::SetPosition()   //判断物品是否出界
{
	int w = GameMessage::rect.Width();
	int h = GameMessage::rect.Height();
	if (x < -width || y < -height || x > w || y > h)
		is_dead = true;
}
void Things::draw(CDC* pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);
	pDC->TransparentBlt(x, y, width, height, &memDC, 0, 0, width, height, RGB(255, 255, 255));
}
void Things::move()
{
	x = x + dir_x * speed;
	y = y + dir_y * speed;
}
