#include "stdafx.h"
#include "Explo.h"
#include "resource.h"
//Explo(int num, int xx, int yy); //在位置xx,yy处进行爆炸
//void loadimage();    //载入图片
//void draw(); //画图
//~Explo();
//int num;	//图组数量
//int length; //单个图片长度
//CBitmap bmp;		//图片
//int width, height;	//模型的大小
//int x, y;			//位置坐标
//int speed;			//速度
//int dir_x, dir_y;	//方向向量
//int hurt;			//每个物品的伤害，包括碰撞伤害，子弹伤害，物品伤害
//bool is_dead;		//判断是否死亡
Explo::Explo(int n, int xx, int yy)
{
	//判断爆炸位置和类型
	x = xx;	y = yy; index = 0;
	if (n == 1)  //小爆炸
	{
		bmp.LoadBitmap(5001);
		length = 33;
		num = 8;

	}
	else if (n == 2)
	{
		bmp.LoadBitmap(5002);
		length = 66;
		num = 8;
	}
	else if (n == 3)
	{
		bmp.LoadBitmap(5003);
		length = 66 * 4;
		num = 8;
	}
	loadimage();
}

Explo::~Explo()
{
}
//加载
void Explo::loadimage()
{
	//加载爆炸图像
	if (!imagelist.Create(length, length, ILC_COLOR24 | ILC_MASK, 8, 0))
		return;
	imagelist.Add(&bmp, RGB(0, 0, 0));
}
//画
void Explo::draw(CDC* cDC)
{
	imagelist.Draw(cDC, index, CPoint(x, y), ILD_TRANSPARENT);
	index++;
	is_end();
}
bool Explo::is_end()
{
	if (index > num)
		goto_die();
	return return_dead();
}