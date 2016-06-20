#pragma once
class Talking
{
public:
	Talking(int num);
	~Talking();
	void draw(CDC* pDC);
	int x, y;
	int width, height;
	CBitmap bmp;
};

