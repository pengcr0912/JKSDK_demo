// IDD_SAVEFILEDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JASDK_demo.h"
#include "IDD_SAVEFILEDlg.h"
#include "afxdialogex.h"
#include "JASDK_demoDlg.h"
#include "JASDK.h"

// CIDD_SAVEFILEDlg 对话框

IMPLEMENT_DYNAMIC(CIDD_SAVEFILEDlg, CDialogEx)

CIDD_SAVEFILEDlg::CIDD_SAVEFILEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIDD_SAVEFILEDlg::IDD, pParent)
{
	saveflag1 = false;
	saveflag2 = false;
}

CIDD_SAVEFILEDlg::~CIDD_SAVEFILEDlg()
{
}

void CIDD_SAVEFILEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, E_SAVEFILE1, filePath1);
	DDX_Control(pDX, E_SAVEFILE2, filePath2);
	DDX_Control(pDX, B_SAVEFILE1, b_save1);
	DDX_Control(pDX, B_SAVEFILE2, b_save2);
}


BEGIN_MESSAGE_MAP(CIDD_SAVEFILEDlg, CDialogEx)
	ON_BN_CLICKED(B_SAVEFILE1, &CIDD_SAVEFILEDlg::OnBnClickedSavefile1)
	ON_BN_CLICKED(B_SAVEFILE2, &CIDD_SAVEFILEDlg::OnBnClickedSavefile2)
END_MESSAGE_MAP()


// CIDD_SAVEFILEDlg 消息处理程序


void CIDD_SAVEFILEDlg::OnBnClickedSavefile1()
{
	// TODO: 在此添加控件通知处理程序代码
	char lpszStringBuf[255];
	memset(lpszStringBuf,0,255);
	filePath1.GetWindowTextA(lpszStringBuf,sizeof(lpszStringBuf));
	if(strlen(lpszStringBuf) >0 && strlen(lpszStringBuf)<256){
		if(saveflag1 == false){
			saveflag1 = true;
			((CJASDK_demoDlg*)demodlg)->saveFile1(lpszStringBuf,strlen(lpszStringBuf),1);
		}else{
			saveflag1 = false;
			((CJASDK_demoDlg*)demodlg)->saveFile1(lpszStringBuf,strlen(lpszStringBuf),0);
		}
	}
	if(saveflag1 == true){
		b_save1.SetWindowTextA("停止录像1");
	}else {
		b_save1.SetWindowTextA("开始录像1");
	}
}

void CIDD_SAVEFILEDlg::setSavePath(void* demodlg,int button,char *path,bool saveflag){
	this->demodlg = demodlg;
	if(button ==1){
		if(saveflag == true){
			saveflag1 = true;;
			if(NULL!=path){
				filePath1.SetWindowTextA(path);
			}
			if(b_save1)
				b_save1.SetWindowTextA("停止录像1");
		}else{
			if(NULL!=path){
				filePath1.SetWindowTextA(path);
			}
			if(b_save1)
				b_save1.SetWindowTextA("开始录像1");
			saveflag1 = false;
		}
		
	}else if(button == 2){
		if(saveflag == true){
			if(NULL!=path){
				filePath2.SetWindowTextA(path);
			}
			if(b_save2)
				b_save2.SetWindowTextA("停止录像2");
			saveflag1 = true;
		}else{
			if(NULL!=path){
				filePath2.SetWindowTextA(path);
			}
			if(b_save2)
				b_save2.SetWindowTextA("开始录像2");
			saveflag1 = false;
		}
	}
}


void CIDD_SAVEFILEDlg::OnBnClickedSavefile2()
{
	// TODO: 在此添加控件通知处理程序代码
	char lpszStringBuf[255];
	memset(lpszStringBuf,0,255);
	filePath2.GetWindowTextA(lpszStringBuf,sizeof(lpszStringBuf));
	if(strlen(lpszStringBuf) >0 && strlen(lpszStringBuf)<256){
		if(saveflag2 == false){
			saveflag2 = true;
			((CJASDK_demoDlg*)demodlg)->saveFile2(lpszStringBuf,strlen(lpszStringBuf),1);
		}else{
			saveflag1 = false;
			((CJASDK_demoDlg*)demodlg)->saveFile2(lpszStringBuf,strlen(lpszStringBuf),0);
		}
	}
	if(saveflag2 == true){
		b_save2.SetWindowTextA("停止录像2");
	}else {
		b_save2.SetWindowTextA("开始录像2");
	}
}
