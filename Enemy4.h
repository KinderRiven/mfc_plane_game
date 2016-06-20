#pragma once
#include "GameMessage.h"
#include "GameNature.h"
//int speed;			//速度.
//bool is_dead;		//判断是否死亡
//CBitmap bmp;		//图片
//int width, height;	//模型的大小
//int x, y;			//位置坐标
//int dir_x, dir_y;	//方向向量
//int hurt;			//每个物品的伤害，包括碰撞伤害，子弹伤害，物品伤害
class Enemy4:
	public GameNature
{
public:
	Enemy4(int x,int y,int dx = 0,int dy = 1);
	~Enemy4();
	void move();
	void SetPos();
	void draw(CDC* pDC);
	int score;
	int life;
};

