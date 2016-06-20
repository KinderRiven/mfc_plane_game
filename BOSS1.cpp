#include "stdafx.h"
#include "BOSS1.h"
#include "GameMessage.h"
#include "GameNature.h"
#include "resource.h"
#include "AllSpeed.h"
#include "AllLife.h"
#include "AllScore.h"
#include "AllHurt.h"
BOSS1::BOSS1(int v,int xx,int yy,int dx,int dy)
{
	speed = AllSpeed::speed_boss;
	score = AllScore::score_boss;
	is_dead = false;
	bmp.LoadBitmap(10000 + v);
	x = xx;	y = yy;
	dir_x = dx;	dir_y = dy;
	if (v == 1)
	{
		Lv = 1;
		hurt = AllHurt::hurt_boss;
		life = AllLife::life_boss1;
		width = 338; height = 219;
	}
	if (v == 2)
	{
		Lv = 2;
		hurt = AllHurt::hurt_boss;
		life = AllLife::life_boss2;
		width = 384;
		height = 307;
	}
	else if (v == 3){
		Lv = 3;
		hurt = AllHurt::hurt_boss;
		life = AllLife::life_boss3;
		width = 400;
		height = 231;
	}
	else if (v == 4){
		Lv = 4;
		hurt = AllHurt::hurt_max_boss;
		life = AllLife::life_boss3;
		width  = 500;
		height = 400;
	}
	else if (v == 5) //ÒÆ¶¯±¤ÀÝ
	{
		Lv = 5;
		width  = 800;
		height = 480;
		hurt = AllHurt::hurt_boss;
		life = AllLife::life_boss5;
		dir_x = 0;	dir_y = 1;
	}

}
BOSS1::~BOSS1()
{
}
void BOSS1::move()
{
	x = x + dir_x * speed;
	y = y + dir_y * speed;
	ChangePos();
}
void BOSS1::ChangePos()
{
	int w = GameMessage::rect.Width();
	int h = GameMessage::rect.Height();
	if (Lv <= 4){
		int h1 = h / 2 - height;
		int w1 = w - width;
		if (x < 0)
		{
			dir_x = 1;
			if (y < 0)  dir_y = 1;
			if (y > h1) dir_y = -1;
		}
		if (x > w1)
		{
			dir_x = -1;
			if (y < 0)  dir_y = 1;
			if (y > h1) dir_y = -1;
		}
		if (y < -height)
		{
			dir_y = 1;
			if (x < 0) dir_x = 1;
			if (x > w1)dir_x = -1;
		}
		if (y > h1)
		{
			dir_y = -1;
			if (x < 0) dir_x = 1;
			if (x > w1)dir_x = -1;
		}
	}
	else if (Lv == 5)
	{
		if (y < - height + 50)		dir_y =  1;
		if (y >= h / 4)				dir_y = -1;
	}
}
void BOSS1::draw(CDC* pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);
	if (!is_dead){
		pDC->TransparentBlt(x, y, width, height, &memDC, 0, 0, width, height, RGB(238, 243, 250));
	}
}
void BOSS1::draw(CDC* pDC,int v)
{
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);
	if (!is_dead){
		pDC->TransparentBlt(x, y, 200, 200, &memDC, 0, 0, width, height, RGB(238, 243, 250));
	}
}
bool BOSS1::Attack()
{
	int t = rand() % 3;
	if (t == 1) return true;
	else return false;
}
