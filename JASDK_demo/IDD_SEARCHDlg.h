#pragma once
#include "JASDK_Discover.h"
//
typedef struct searchData{
	pstJASDKSearchItem item;
	searchData* next;
}STSEARCHDATA,*LPSEARCHDATA; 

// IDD_SEARCHDlg 对话框

class IDD_SEARCHDlg : public CDialogEx
{
	DECLARE_DYNAMIC(IDD_SEARCHDlg)

public:
	IDD_SEARCHDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~IDD_SEARCHDlg();
	bool stopSearch;
	Handler handler;
	CButton m_cbSearch;
	CListCtrl m_ctrlDetectList;
	stJASDK_SETUP_IP_INFO st_info;
	stJASDK_SETUP_IP_INFO st_info_new;
	int g_index;
	void notifyItemData(pstJASDKSearchItem pInfo, LPVOID pUser);
	void notifySetIP(pstJASDKSetIPItem info, LPVOID pUser);
	void * demodlg;
// 对话框数据
	enum { IDD = IDD_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	CIPAddressCtrl ip_addr_edit;
	CIPAddressCtrl netmask_edit;
	CIPAddressCtrl gateway_edit;
	CEdit          port_edit;
	CEdit          username_edit;
	CEdit          password_edit;
	CIPAddressCtrl ip_addr_shoudong;

	
	LPSEARCHDATA first;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSearch1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSearchSetip();
   void setCJASDK_demoDlg(void* demodlg);
   afx_msg void OnBnClickedButton1();

   afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
