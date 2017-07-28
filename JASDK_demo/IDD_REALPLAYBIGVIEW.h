#pragma once


// CIDD_REALPLAYBIGVIEW 对话框

class CIDD_REALPLAYBIGVIEW : public CDialogEx
{
	DECLARE_DYNAMIC(CIDD_REALPLAYBIGVIEW)

public:
	CIDD_REALPLAYBIGVIEW(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIDD_REALPLAYBIGVIEW();

// 对话框数据
	enum { IDD = IDD_REALPLAYBIGVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();
	BOOL setMainDialogInfo(void* dlg,HWND dlg_Hwnd,LONG lUserID);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

private:
	void* mainDlg;
	void* mainDlg_hwnd;


};
