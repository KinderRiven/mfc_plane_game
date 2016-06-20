// AboutMe.cpp : 实现文件
//

#include "stdafx.h"
#include "MyGame.h"
#include "AboutMe.h"
#include "afxdialogex.h"


// AboutMe 对话框

IMPLEMENT_DYNAMIC(AboutMe, CDialogEx)

AboutMe::AboutMe(CWnd* pParent /*=NULL*/)
	: CDialogEx(AboutMe::IDD, pParent)
{

}

AboutMe::~AboutMe()
{
}

void AboutMe::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutMe, CDialogEx)
END_MESSAGE_MAP()


// AboutMe 消息处理程序
