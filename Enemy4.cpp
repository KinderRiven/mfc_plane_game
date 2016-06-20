#include "stdafx.h"
#include "Enemy4.h"
#include "AllHurt.h"
#include "AllLife.h"
#include "AllScore.h"
#include "AllSpeed.h"
#include "GameMessage.h"
//int speed;			//速度.
//bool is_dead;		//判断是否死亡
//CBitmap bmp;		//图片
//int width, height;	//模型的大小
//int x, y;			//位置坐标
//int dir_x, dir_y;	//方向向量
//int hurt;			//每个物品的伤害，包括碰撞伤害，子弹伤害，物品伤害
Enemy4::Enemy4(int xx,int yy,int dx,int dy)
{
	x = xx; y = yy; dir_x = dx; dir_y = dy;
	width = 200; height = 121;
	speed = AllSpeed::speed_enemy4;
	hurt  = AllHurt::hurt_enemy4;
	score = AllScore::score_enemy4;
	life  = AllLife::life_enemy4;
	is_dead = false;
	bmp.LoadBitmap(Enemy_y5);
}
Enemy4::~Enemy4()
{
}
void Enemy4::move()
{
	x = x + dir_x * speed;
	y = y + dir_y * speed;
	SetPos();
}
void Enemy4::SetPos()
{
	int w = GameMessage::rect.Width();
	int h = GameMessage::rect.Height();
	if (y > h) y = -200;
}
void Enemy4::draw(CDC* pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);
	if (!is_dead){
		pDC->TransparentBlt(x, y, 150, 100, &memDC, 0, 0, width, height, RGB(0, 0, 0));
	}
}