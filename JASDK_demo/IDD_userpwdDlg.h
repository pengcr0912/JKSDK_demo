#pragma once


// CIDD_userpwdDlg �Ի���

class CIDD_userpwdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIDD_userpwdDlg)

public:
	CIDD_userpwdDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIDD_userpwdDlg();

// �Ի�������
	enum { IDD = IDD_USERPWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void setDemoDlg(void* demoDlg);


private:
	void* mainDlg;
public:
	afx_msg void OnBnClickedCancel();
};
