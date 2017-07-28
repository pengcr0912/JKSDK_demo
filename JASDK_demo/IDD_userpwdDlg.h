#pragma once


// CIDD_userpwdDlg 对话框

class CIDD_userpwdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIDD_userpwdDlg)

public:
	CIDD_userpwdDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIDD_userpwdDlg();

// 对话框数据
	enum { IDD = IDD_USERPWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void setDemoDlg(void* demoDlg);


private:
	void* mainDlg;
public:
	afx_msg void OnBnClickedCancel();
};
