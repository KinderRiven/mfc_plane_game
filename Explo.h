#pragma once
#include "GameNature.h"
class Explo:
	public GameNature
{
public:
	Explo(int num,int xx,int yy); //在位置xx,yy处进行爆炸
	void loadimage();    //载入图片
	void draw(CDC* cDC); //画图
	bool is_end();	//爆炸结束
	~Explo();
	int index;  //目前的位置
	int num;	//图组数量
	int length; //单个图片长度
	CImageList imagelist;
};