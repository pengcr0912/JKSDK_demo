// IDD_REALPLAYBIGVIEW.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JASDK_demo.h"
#include "IDD_REALPLAYBIGVIEW.h"
#include "afxdialogex.h"


// CIDD_REALPLAYBIGVIEW �Ի���

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



// CIDD_REALPLAYBIGVIEW ��Ϣ�������


void CIDD_REALPLAYBIGVIEW::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
