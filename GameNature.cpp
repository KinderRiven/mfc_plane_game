#include "stdafx.h"
#include "GameNature.h"
#include "GameMessage.h"

int  GameNature::return_width()
{
	return width;
}
int  GameNature::return_height()
{
	return height;
}
int  GameNature::return_x()
{
	return x;
}
int  GameNature::return_y()
{
	return y;
}
int  GameNature::return_hurt()
{
	return hurt;
}
void GameNature::goto_die()
{
	is_dead = true;
}
GameNature::GameNature()
{
	is_dead = false;
}
GameNature::~GameNature()
{
}
void GameNature::UpDatePos() //根据位置判断边界
{
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x + width > GameMessage::rect.Width()) 
		x = GameMessage::rect.Width() - width;
	if (y + height > GameMessage::rect.Height())
		y = GameMessage::rect.Height() - height;
}
void GameNature::move()
{
	x = x + dir_x * speed;
	y = y + dir_y * speed;
}
void GameNature::draw(CDC *pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);
	if (!is_dead)
	{
		UpDatePos();
		pDC->TransparentBlt(x, y, width, height, &memDC, 0, 0, width, height, RGB(238, 243, 250));
	}
}
bool GameNature::return_dead()
{
	return is_dead;
}