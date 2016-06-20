// Help.cpp : 实现文件
//

#include "stdafx.h"
#include "MyGame.h"
#include "Help.h"
#include "afxdialogex.h"


// Help 对话框

IMPLEMENT_DYNAMIC(Help, CDialogEx)

Help::Help(CWnd* pParent /*=NULL*/)
	: CDialogEx(Help::IDD, pParent)
{

}

Help::~Help()
{
}

void Help::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Help, CDialogEx)
END_MESSAGE_MAP()


// Help 消息处理程序
