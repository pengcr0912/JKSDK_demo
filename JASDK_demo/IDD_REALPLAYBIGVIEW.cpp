// IDD_REALPLAYBIGVIEW.cpp : 实现文件
//

#include "stdafx.h"
#include "JASDK_demo.h"
#include "IDD_REALPLAYBIGVIEW.h"
#include "afxdialogex.h"


// CIDD_REALPLAYBIGVIEW 对话框

IMPLEMENT_DYNAMIC(CIDD_REALPLAYBIGVIEW, CDialogEx)

CIDD_REALPLAYBIGVIEW::CIDD_REALPLAYBIGVIEW(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIDD_REALPLAYBIGVIEW::IDD, pParent)
{

}

CIDD_REALPLAYBIGVIEW::~CIDD_REALPLAYBIGVIEW()
{
}

void CIDD_REALPLAYBIGVIEW::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIDD_REALPLAYBIGVIEW, CDialogEx)
	ON_BN_CLICKED(IDOK, &CIDD_REALPLAYBIGVIEW::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CIDD_REALPLAYBIGVIEW::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ShowWindow(SW_SHOWMAXIMIZED);
	return TRUE;
}



// CIDD_REALPLAYBIGVIEW 消息处理程序


void CIDD_REALPLAYBIGVIEW::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
