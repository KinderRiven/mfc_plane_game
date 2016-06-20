#pragma once
#include "GameNature.h"
class GameWord:
	public GameNature
{
public:
	GameWord(CString w, int start, int end,int x,int y);
	void draw(CDC* cDC);
	~GameWord();
	CString word;
	int start, end;
};

