
// JASDK_demoDlg.h : ͷ�ļ�
//
#include "IDD_SEARCHDlg.h"
#include "IDD_SAVEFILEDlg.h"
#include "PlayBackDlg.h"
#include "IDD_userpwdDlg.h"
#include "IDD_PTZ_DLG.h"

#pragma once

#define DISPLAY_NUM 4
#pragma comment(lib,"JASDK_DLL.lib")

// CJASDK_demoDlg �Ի���
class CJASDK_demoDlg : public CDialogEx
{
// ����
public:
	CJASDK_demoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_JASDK_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	IDD_SEARCHDlg searchDlg;
	CIDD_PTZ_DLG ptz_dlg;
	CIDD_SAVEFILEDlg saveFileDlg;
	CPlayBackDlg   playBackDlg;
	CIDD_userpwdDlg userPwdDlg;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDevice();
	void setSearchInfo(pstJASDKSearchItem info);

private:
	int curnum;
	LONG userId[DISPLAY_NUM];
	LONG RealPlay_handle[DISPLAY_NUM];


public:
	CButton b_luxiang_l;
	void thread_process_login(pstJASDKSearchItem info,int thread);
	afx_msg void OnBnClickedSetConfig();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedLuxiang();
	
	char filepath1[255];
	char filepath2[255];
	char filepath_avi[255];
	char username[255];
	char password[255];
	bool b_savefile1;
	bool b_savefile2;
	bool b_savefile_avi;
	FILE* fp;
	int i_num;
	// flag 0 ֹͣ¼��1��ʼ¼��
	void saveFile1(char* path1,int length,int flag);
	void saveFile2(char* path2,int length,int flag);
	void saveFile_avi(char* avipath,int length,int flag);
	void notifyData(LONG lRealHandle, DWORD dwDataType,BYTE *pBuffer,DWORD dwBufSize);
	afx_msg void OnBnClickedHuifang();
	afx_msg void OnBnClickedZhuatu();
	afx_msg void OnBnClickedCancel();
	void setUserPassword(char* username,int userlen,char*pwd,int pwdlen);
	void sdknotify_ExceptionMessage(LONG lUserID,LONG lHandle,DWORD dwType,DWORD exNum,void *pUser);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedStopreal();
	afx_msg void OnBnClickedRealplay();
	afx_msg void OnBnClickedYuntai();

	void setRealPlayWND(int wndNUM);
};
