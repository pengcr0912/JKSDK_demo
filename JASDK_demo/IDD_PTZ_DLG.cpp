// IDD_PTZ_DLG.cpp : 实现文件
//

#include "stdafx.h"
#include "JASDK_demo.h"
#include "IDD_PTZ_DLG.h"
#include "afxdialogex.h"
#include "JASDK.h"
#include "JASDK_demoDlg.h"


// CIDD_PTZ_DLG 对话框

IMPLEMENT_DYNAMIC(CIDD_PTZ_DLG, CDialogEx)

CIDD_PTZ_DLG::CIDD_PTZ_DLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIDD_PTZ_DLG::IDD, pParent)
{

}

CIDD_PTZ_DLG::~CIDD_PTZ_DLG()
{
}

void CIDD_PTZ_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIDD_PTZ_DLG, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CIDD_PTZ_DLG::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_PTZ_UP_1, &CIDD_PTZ_DLG::OnBnClickedPtzUp1)
	ON_BN_CLICKED(IDC_PTZ_AUTOPAN, &CIDD_PTZ_DLG::OnBnClickedPtzAutopan)
	ON_BN_CLICKED(IDC_PTZ_STOP, &CIDD_PTZ_DLG::OnBnClickedPtzStop)
	ON_BN_CLICKED(IDC_PTZ_FOCUS_FAR, &CIDD_PTZ_DLG::OnBnClickedPtzFocusFar)
END_MESSAGE_MAP()


// CIDD_PTZ_DLG 消息处理程序
BOOL CIDD_PTZ_DLG::OnInitDialog(){
	CDialogEx::OnInitDialog();
	realPlayWnd = GetDlgItem(IDE_STATIC_PIC_PTZ)->GetSafeHwnd();
	JASDK_setRealPlayWindow(lUserID,realPlayWnd);
	return TRUE;
}

void CIDD_PTZ_DLG::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	((CJASDK_demoDlg*)JASDK_demo)->setRealPlayWND(1);
	CDialogEx::OnCancel();
}

void CIDD_PTZ_DLG::setCJASDK_demoDlg(void* sdkd,int userid){
	JASDK_demo = sdkd;
	lUserID = userid;
}

void CIDD_PTZ_DLG::OnBnClickedPtzUp1()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CIDD_PTZ_DLG::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_LBUTTONDOWN)
	{
		if(pMsg->hwnd == GetDlgItem(IDC_PTZ_UP_1)->m_hWnd)
		{
			// 按钮按下
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_UP, 1, 1,0);
		}else if(pMsg->hwnd == GetDlgItem(IDC_PTZ_LEFT_1)->m_hWnd)
		{
			// 按钮按下
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_LEFT, 1, 1,0);
		}else if(pMsg->hwnd == GetDlgItem(IDC_PTZ_DOWN_1)->m_hWnd)
		{
			// 按钮按下
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_DOWN, 1, 1,0);
		}else if(pMsg->hwnd == GetDlgItem(IDC_PTZ_RIGHT_1)->m_hWnd)
		{
			// 按钮按下
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_RIGHT, 1, 1,0);
		}
		else if(pMsg->hwnd == GetDlgItem(IDC_PTZ_FOCUS_FAR)->m_hWnd)
		{
			// 按钮按下
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_FOCUS_FAR, 1, 1,0);
		}
		else if(pMsg->hwnd == GetDlgItem(IDC_PTZ_FOCUS_NEAR)->m_hWnd)
		{
			// 按钮按下
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_FOCUS_NEAR, 1, 1,0);
		}else if(pMsg->hwnd == GetDlgItem(IDC_PTZ_ZOOM_IN)->m_hWnd)
		{
			// 按钮按下
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_ZOOM_IN, 1, 1,0);
		}else if(pMsg->hwnd == GetDlgItem(IDC_PTZ_ZOOM_OUT)->m_hWnd)
		{
			// 按钮按下
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_ZOOM_OUT, 1, 1,0);
		}			
	}
	else if(pMsg->message == WM_LBUTTONUP)
	{
		if(pMsg->hwnd == GetDlgItem(IDC_PTZ_UP_1)->m_hWnd)
		{
			// 按钮弹起
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_UP, 0, 0,0);
		}else if(pMsg->hwnd == GetDlgItem(IDC_PTZ_LEFT_1)->m_hWnd)
		{
			// 按钮弹起
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_LEFT, 0, 0,0);
		}else if(pMsg->hwnd == GetDlgItem(IDC_PTZ_DOWN_1)->m_hWnd)
		{
			// 按钮弹起
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_DOWN, 0, 0,0);
		}else if(pMsg->hwnd == GetDlgItem(IDC_PTZ_RIGHT_1)->m_hWnd)
		{
			// 按钮弹起
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_RIGHT, 0, 0,0);
		}else if(pMsg->hwnd == GetDlgItem(IDC_PTZ_FOCUS_FAR)->m_hWnd)
		{
			// 按钮弹起
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_FOCUS_FAR, 0, 0,0);
		}else if(pMsg->hwnd == GetDlgItem(IDC_PTZ_FOCUS_NEAR)->m_hWnd)
		{
			// 按钮弹起
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_FOCUS_NEAR, 0, 0,0);
		}else if(pMsg->hwnd == GetDlgItem(IDC_PTZ_ZOOM_OUT)->m_hWnd)
		{
			// 按钮弹起
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_ZOOM_OUT, 0, 0,0);
		}else if(pMsg->hwnd == GetDlgItem(IDC_PTZ_ZOOM_IN)->m_hWnd)
		{
			// 按钮弹起
			JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_ZOOM_IN, 0, 0,0);
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
} 

void CIDD_PTZ_DLG::OnBnClickedPtzAutopan()
{
	// TODO: 在此添加控件通知处理程序代码
	JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_AUTOPAN, 1, 1,0);
}


void CIDD_PTZ_DLG::OnBnClickedPtzStop()
{
	// TODO: 在此添加控件通知处理程序代码
	JASDK_PTZ_CTRL(lUserID,1,JASDK_PTZ_CMD_STOP, 0, 0,0);
}


void CIDD_PTZ_DLG::OnBnClickedPtzFocusFar()
{
	// TODO: 在此添加控件通知处理程序代码
}
