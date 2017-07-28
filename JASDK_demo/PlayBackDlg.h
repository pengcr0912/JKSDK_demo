#pragma once
#include "JASDK.h"


// CPlayBackDlg 对话框

class CPlayBackDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPlayBackDlg)

public:
	CPlayBackDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPlayBackDlg();
	CDateTimeCtrl D_m_dateCtrlstart;
	CDateTimeCtrl D_m_dateCtrlstop;
	CButton		B_playBackSearch;
	BOOL OnInitDialog();
	void setCJASDK_demoDlg(void* sdk,int userid);
// 对话框数据
	enum { IDD = IDD_PLAYBACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPlaybacksearch();


private:
	CListCtrl m_ctrlDetectList;
	void* JASDK_demo;
	LONG lUserID;
	LONG pbSearchHandle;
	int g_index;
	bool b_pb_play;
	LONG pbPlayHandle;
	int i_num;
	FILE* fpcall;
	HWND PlaybackWnd;
	CButton pbPlay;
	CButton pbPause;
	CButton pbPlayPlay;
	CButton pbZhuaTu;
	CButton pbDownload;

	bool downloadFile;
	LONG PBDownloadFile;
	LONG PBDownloadCallBack;
public:
	afx_msg void OnBnClickedPbPlay();
	afx_msg void OnBnClickedPbPause();
	afx_msg void OnBnClickedPbPlayPlay();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	void callBack(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize);

	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedOk();
};
