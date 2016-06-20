#include "stdafx.h"
#include "Enemy5.h"
#include "GameMessage.h"
#include "AllHurt.h"
#include "AllLife.h"
#include "AllScore.h"
#include "AllSpeed.h"
Enemy5::Enemy5(int lv,int xx,int yy,int dx,int dy)
{
	x = xx; y = yy; dir_x = dx; dir_y = dy;
	//方向大小位置
	width = 258; height = 244;
	speed = AllSpeed::speed_enemy5;
	hurt = AllHurt::hurt_enemy5;
	score = AllScore::score_enemy5;
	life = AllLife::life_enemy5;
	can_attack = 0;
	is_dead = false;
	if (lv == 1){
		bmp.LoadBitmap(Enemy_y7);
	}
	if(lv == 2){
		bmp.LoadBitmap(Enemy_y8);
	}
	if (lv == 3){
		bmp.LoadBitmap(Enemy_y6);
	}
}

Enemy5::~Enemy5()
{
}

bool Enemy5::SetPos()
{
	int w = GameMessage::rect.Width();
	int h = GameMessage::rect.Height();
	if (y < h / 4) return true;
	else if (y < h / 3)
	{
		dir_x = 0;
		can_attack = 1;
		bmp.DeleteObject();
		bmp.LoadBitmap(Enemy_y6);
		return true;
	}
	else
		return false;
}
void Enemy5::move()
{
	if (SetPos()){
		x = x + dir_x * speed;
		y = y + dir_y * speed;
	}
}
void Enemy5::draw(CDC* pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);
	if (!is_dead){
		pDC->TransparentBlt(x, y, 258, 244, &memDC, 0, 0, width, height, RGB(0, 0, 0));
	}
}
bool Enemy5::Attack()
{
	int t = rand() % 20;
	if (t == 1)
		return can_attack;
	else
		return false;
}