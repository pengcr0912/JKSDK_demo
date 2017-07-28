#pragma once


// CIDD_SAVEFILEDlg 对话框

class CIDD_SAVEFILEDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIDD_SAVEFILEDlg)

public:
	CIDD_SAVEFILEDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIDD_SAVEFILEDlg();

	CEdit filePath1;
	CEdit filePath2;
	CButton b_save1;
	CButton b_save2;

	void* demodlg;
	bool saveflag1;
	bool saveflag2;
// 对话框数据
	enum { IDD = IDD_SAVEFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSavefile1();
	void setSavePath(void* demodlg,int button,char *path,bool flag);
	afx_msg void OnBnClickedSavefile2();
};
