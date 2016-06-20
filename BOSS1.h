#pragma once
#include "GameNature.h"
//GameNature();
//~GameNature();
//virtual void draw(CDC* pDC);//画图函数
//virtual void move();
//void UpDatePos();
//bool return_dead();
//int  return_width();
//int  return_height();
//int  return_x();
//int  return_y();
//int  return_hurt();
//void goto_die();
//int speed;			//速度.
//bool is_dead;		//判断是否死亡
//protected:
//	CBitmap bmp;		//图片
//	int width, height;	//模型的大小
//	int x, y;			//位置坐标
//	int dir_x, dir_y;	//方向向量
//	int hurt;			//每个物品的伤害，包括碰撞伤害，子弹伤害，物品伤害
class BOSS1:
	public GameNature
{
public:
	BOSS1(int v,int x,int y,int dx = -1,int dy = -1);
	~BOSS1();
	void move();
	void draw(CDC* pDC);
	void draw(CDC* pDC,int v);
	void ChangePos();
	bool Attack();
	int speed;
	int Lv;//Boss种类
	int life;
	int score;
};

