#include "stdafx.h"
#include "Enemy1.h"
#include "GameMessage.h"
#include "AllLife.h"
#include "AllScore.h"
#include "AllHurt.h"
//  敌人一号
//	GameNature();
//	~GameNature();
//	virtual void draw(CDC* pDC);//画图函数
//	virtual void move();
//	void UpDatePos();
//	CBitmap bmp;		//图片
//	int width, height;	//模型的大小
//	int x, y;			//位置坐标
//	int speed;			//速度
//	int dir_x, dir_y;	//方向向量
//	int hurt;			//每个物品的伤害，包括碰撞伤害，子弹伤害，物品伤害
//	bool is_dead;		//判断是否死亡
Enemy1::Enemy1()
{
	int w = GameMessage::rect.Width();
	int h = GameMessage::rect.Height();
	is_dead = false; //或者的
	life = AllLife::life_enemy1;
	width = 208; height = 157;
	x = rand() % w;   y = -300;
	speed = rand() % 15 + 5;
	dir_x = 0; dir_y = 1;	//方向一开始都向下
	hurt = AllHurt::hurt_enemy1;			//碰撞伤害
	score = AllScore::score_enemy1;			//击落的得分
	bmp.LoadBitmap(3001);	//加载位图
	if (x + width > w) x = w - width;
}
Enemy1::~Enemy1()
{
}
void Enemy1::move()
{
	x = x + dir_x * speed;
	y = y + dir_y * speed;
	Change_Dir(); //改变移动轨迹
}
void Enemy1::Change_Dir()
{
	int h = GameMessage::rect.Height();
	if (y > h/3) //往回飞
	{
		speed = rand() % 10 + 5;
		dir_x = 0;
		dir_y = -1;
	}
	if (y < -50) //往前飞
	{
		speed = rand() % 20 + 5;
		dir_x = 0;
		dir_y = 1;
	}
}
void Enemy1::draw(CDC *pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);
	if (!is_dead){
		pDC->TransparentBlt(x, y, width, height, &memDC, 0, 0, width, height, RGB(255, 255, 255));
	}
}
bool Enemy1::Attack()
{
	int t = rand() % 10;
	if (t == 3) return true;
	else return false;
}