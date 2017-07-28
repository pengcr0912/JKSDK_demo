#pragma once


// CIDD_PTZ_DLG 对话框

class CIDD_PTZ_DLG : public CDialogEx
{
	DECLARE_DYNAMIC(CIDD_PTZ_DLG)

public:
	CIDD_PTZ_DLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIDD_PTZ_DLG();
	VOID setCJASDK_demoDlg(void* sdkd,int userid);
	BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_PTZ_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();

private:
	void* JASDK_demo;
	LONG lUserID;
	HWND realPlayWnd;
	CButton ptz_up_1;
	CButton ptz_left_1;
	CButton ptz_right_1;
	CButton ptz_down_1;
public:
	afx_msg void OnBnClickedPtzUp1();
	afx_msg void OnBnClickedPtzAutopan();
	afx_msg void OnBnClickedPtzStop();
	afx_msg void OnBnClickedPtzFocusFar();
};
