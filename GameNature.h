#pragma once
//关于所有物品的属性父函数
//速度 位置 方向 是否存在 图片
class GameNature:
	public CObject
{
public:
	GameNature();
	~GameNature();
	virtual void draw(CDC* pDC);//画图函数
	virtual void move();
	void UpDatePos();
	bool return_dead();
	int  return_width();
	int  return_height();
	int  return_x();
	int  return_y();
	int  return_hurt();
	void goto_die();
	int speed;			//速度.
	bool is_dead;		//判断是否死亡
protected:
	CBitmap bmp;		//图片
	int width, height;	//模型的大小
	int x,y;			//位置坐标
	int dir_x, dir_y;	//方向向量
	int hurt;			//每个物品的伤害，包括碰撞伤害，子弹伤害，物品伤害
};

	