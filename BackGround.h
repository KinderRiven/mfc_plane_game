#pragma once
#include "GameNature.h"
class BackGround:
	public GameNature
{
public:
	BackGround(int num,int speed);
	BackGround(int num,int x,int y,int dir_x,int dir_y,int speed);
	~BackGround();
	CBitmap bmp;
	void PaintPicture(CDC *pDC);
	void PaintPicture2(CDC *pDC);
	int width;
	int height;
};

