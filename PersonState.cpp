#include "stdafx.h"
#include "PersonState.h"
#include "GameNature.h"
#include "GameMessage.h"
#include "resource.h"
//public:
//	GameNature();
//	~GameNature();
//	virtual void draw(CDC* pDC);//画图函数
//	virtual void move();
//	void UpDatePos();
//	bool return_dead();
//	int  return_width();
//	int  return_height();
//	int  return_x();
//	int  return_y();
//	int  return_hurt();
//	void goto_die();
//protected:
//	CBitmap bmp;		//图片
//	int width, height;	//模型的大小
//	int x, y;			//位置坐标
//	int speed;			//速度
//	int dir_x, dir_y;	//方向向量
//	int hurt;			//每个物品的伤害，包括碰撞伤害，子弹伤害，物品伤害
//	bool is_dead;		//判断是否死亡
//	242 138 为窗口大小
PersonState::PersonState(int num)
{
	if (num == 1)	 //定义玩家1的状态栏
	{
		player = 1;
		x = 0; y = 0; //状态栏坐标
		width  = 242;
		height = 138;
		bmp.LoadBitmap(1113);
		score_bmp.LoadBitmap(112);
	}
	if (num == 2)
	{
		player = 2;
		x = 0; y = 0; //状态栏坐标
		width = 242;
		height = 138;
		bmp.LoadBitmap(1114);
		score_bmp.LoadBitmap(112);
	}
}
PersonState::~PersonState()
{
}
void PersonState::draw(CDC* pDC)
{
	int w = GameMessage::rect.Width();
	int h = GameMessage::rect.Height();
	if (player == 1){
		CDC memDC;
		memDC.CreateCompatibleDC(NULL);
		memDC.SelectObject(&bmp);
		pDC->TransparentBlt(x, y, 220, 130, &memDC, 0, 0, 242, 138, RGB(238, 243, 250));
		memDC.SelectObject(&score_bmp);
		pDC->TransparentBlt(x, h - 35, 100, 35, &memDC, 0, 0, 200, 55, RGB(0, 0, 0));
	}
	if (player == 2){
		CDC memDC;
		memDC.CreateCompatibleDC(NULL);
		memDC.SelectObject(&bmp);
		pDC->TransparentBlt(w - width + 22, y, 220, 130, &memDC, 0, 0, 242, 138, RGB(238, 243, 250));
		memDC.SelectObject(&score_bmp);
		pDC->TransparentBlt(w - 100, h - 35, 100, 35, &memDC, 0, 0, 200, 55, RGB(0, 0, 0));
	}
}