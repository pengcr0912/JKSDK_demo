// IDD_userpwdDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JASDK_demo.h"
#include "IDD_userpwdDlg.h"
#include "afxdialogex.h"
#include "JASDK_demoDlg.h"

// CIDD_userpwdDlg �Ի���

IMPLEMENT_DYNAMIC(CIDD_userpwdDlg, CDialogEx)

CIDD_userpwdDlg::CIDD_userpwdDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIDD_userpwdDlg::IDD, pParent)
{

}

CIDD_userpwdDlg::~CIDD_userpwdDlg()
{
}

void CIDD_userpwdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIDD_userpwdDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CIDD_userpwdDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CIDD_userpwdDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CIDD_userpwdDlg ��Ϣ�������


void CIDD_userpwdDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char username[64] ={0};
	char password[64] ={0};
	(CEdit*)GetDlgItem(IDC_USERNAME)->GetWindowTextA(username,sizeof(username));
	(CEdit*)GetDlgItem(IDC_PASSWORD)->GetWindowTextA(password,sizeof(password));
	if(mainDlg)
		((CJASDK_demoDlg*)mainDlg)->setUserPassword(username,strlen(username),password,strlen(password));
	CDialogEx::OnOK();
}


void CIDD_userpwdDlg::setDemoDlg(void* dlg){
	mainDlg = dlg;
}



void CIDD_userpwdDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char username[64] ={0};
	char password[64] ={0};
	if(mainDlg)
		((CJASDK_demoDlg*)mainDlg)->setUserPassword(username,strlen(username),password,strlen(password));
	CDialogEx::OnCancel();
}
