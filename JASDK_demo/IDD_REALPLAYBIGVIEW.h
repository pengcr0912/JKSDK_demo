#pragma once


// CIDD_REALPLAYBIGVIEW �Ի���

class CIDD_REALPLAYBIGVIEW : public CDialogEx
{
	DECLARE_DYNAMIC(CIDD_REALPLAYBIGVIEW)

public:
	CIDD_REALPLAYBIGVIEW(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIDD_REALPLAYBIGVIEW();

// �Ի�������
	enum { IDD = IDD_REALPLAYBIGVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();
	BOOL setMainDialogInfo(void* dlg,HWND dlg_Hwnd,LONG lUserID);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

private:
	void* mainDlg;
	void* mainDlg_hwnd;


};
