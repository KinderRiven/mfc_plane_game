#include "stdafx.h"
#include "GameWord.h"
#include "GameMessage.h"
//Format(_T"Hello,world! %d",n);
GameWord::GameWord(CString w,int s,int e,int xx,int yy) //坐标
{
	word = w;
	start = s;end = e;
	x = xx;	  y = yy;
}
void GameWord::draw(CDC* cDC)
{
	cDC->SetBkMode(TRANSPARENT);//透明处理
	cDC->SetTextColor(RGB(0, 0, 0));
	cDC->TextOut(x, y, word);
	start++;			//文字显示，用来判断时间
}
GameWord::~GameWord()
{

}
