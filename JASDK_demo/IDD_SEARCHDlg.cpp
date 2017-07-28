// IDD_SEARCHDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JASDK_demo.h"
#include "IDD_SEARCHDlg.h"
#include "afxdialogex.h"
#include "JASDK_Discover.h"
#include "JASDK_demoDlg.h"
// IDD_SEARCHDlg 对话框

#define LIST_COLUMN_NUMBER (0)
#define LIST_COLUMN_TYPE (1)
#define LIST_COLUMN_NAME (2)
#define LIST_COLUMN_IP (3)
#define LIST_COLUMN_NETMASK (4)
#define LIST_COLUMN_GATEWAY (5)
#define LIST_COLUMN_MAC (6)
#define LIST_COLUMN_PORT (7)
#define LIST_COMLUMN_ESEE_ID (8)
#define LIST_COLUMN_DEVICE_ID (9)
#define LIST_COLUMN_MANUFATURER (10)
#define LIST_COLUMN_PWD_TYPE (11)



const void search_notifyItemData(pstJASDKSearchItem pInfo, LPVOID pUser){
	 ((IDD_SEARCHDlg*)pUser)->notifyItemData(pInfo,pUser);
}

 const void search_notifySetIP(pstJASDKSetIPItem pInfo, LPVOID pUser){
	 ((IDD_SEARCHDlg*)pUser)->notifySetIP(pInfo,pUser);
}
 /*
 const void search_notifyHelloBye(pstNetsdkHelloByeItem pInfo, LPVOID pUser){
	 ((CNetSDK_SearchDlg*)pUser)->notifyHelloBye(pInfo,pUser);
}
*/

 
void IDD_SEARCHDlg::notifyItemData(pstJASDKSearchItem pInfo, LPVOID pUser){
	char str_number[16];
	memset(str_number, 0, sizeof(str_number));
	_snprintf(str_number, sizeof(str_number), "%d", g_index+1);
	int i =0;
	char ip_addr[32];
	for(i =0 ;i<g_index;i++){
		 m_ctrlDetectList.GetItemText(i, LIST_COLUMN_IP,(LPTSTR)&ip_addr,sizeof(ip_addr));
		 if(strcmp(ip_addr,pInfo->ip)==0){
			return ;
		 }				
	}

	//插入链表
	LPSEARCHDATA tmp = (LPSEARCHDATA)calloc(1,sizeof(STSEARCHDATA));
	if(NULL == tmp){
		return ;
	}
	memset(tmp,0,sizeof(STSEARCHDATA));
	pstJASDKSearchItem item = (pstJASDKSearchItem)calloc(1,sizeof(stJASDKSearchItem));
	if(NULL == item){
		free(tmp);
		tmp ==NULL;
		return;
	}
	memset(item,0,sizeof(stJASDKSearchItem));
	tmp->item = item;
	tmp->next = NULL;

	if(NULL == first){
		first = tmp;		
	}else{
		LPSEARCHDATA tmp_s = first;
		while(tmp_s->next){
			tmp_s = tmp_s->next;			
		}
		tmp_s->next = tmp;
	}

	memcpy(item,pInfo,sizeof(stJASDKSearchItem));

	m_ctrlDetectList.InsertItem(g_index, (LPCTSTR)str_number);
	m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_NUMBER, LPCTSTR(str_number));
	m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_TYPE, LPCTSTR(pInfo->device_model));
	m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_NAME, LPCTSTR(pInfo->name));
	m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_IP, (LPCTSTR)pInfo->ip);
	m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_NETMASK, (LPCTSTR)pInfo->netmask);
	m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_GATEWAY, (LPCTSTR)pInfo->gateway);
	m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_MAC, (LPCTSTR)pInfo->mac);
	m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_PORT, (LPCTSTR)pInfo->software_version);
	m_ctrlDetectList.SetItemText(g_index, LIST_COMLUMN_ESEE_ID, (LPCTSTR)pInfo->esee_id);
	m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_DEVICE_ID, (LPCTSTR)pInfo->device_id);
	m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_MANUFATURER, (LPCTSTR)pInfo->factory_Info);
	m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_PWD_TYPE, (LPCTSTR)(pInfo->password_type == PWD_TYPE_MD5? "MD5":"none"));
	g_index ++;


}

void IDD_SEARCHDlg::notifySetIP(pstJASDKSetIPItem info, LPVOID pUser){
	CString str;
	if(info->status == SETIP_STATUS_OK ){
		str+=("ip 设置完毕，请重新搜索");
	}else{
		str+=("ip 设置失败，请重新搜索");
	}	
	MessageBox(str);

}


IMPLEMENT_DYNAMIC(IDD_SEARCHDlg, CDialogEx)

IDD_SEARCHDlg::IDD_SEARCHDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEARCHDlg::IDD, pParent)
{
	first = NULL;
}

IDD_SEARCHDlg::~IDD_SEARCHDlg()
{
	//删除链表
	while(first){
		LPSEARCHDATA d_s = first;
		first = first->next;
		if(d_s){
			if(d_s->item){
				free(d_s->item);
				d_s->item = NULL;
			}
			d_s->next = NULL;
			free(d_s);
			d_s = NULL;
		}

	}

}

void IDD_SEARCHDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ctrlDetectList);
	DDX_Control(pDX, B_SEARCH_1, m_cbSearch);
	DDX_Control(pDX, IDC_IP1, ip_addr_edit);
	DDX_Control(pDX, IDC_SEARCH_MASK2, netmask_edit);
	DDX_Control(pDX, IDC_SEARCH_GATE4, gateway_edit);
	DDX_Control(pDX, IDC_SEARCH_PORT1, port_edit);
	DDX_Control(pDX, IDC_EDIT2, username_edit);
	DDX_Control(pDX, IDC_EDIT3, password_edit);
	DDX_Control(pDX, IDC_SHOUDONG_IPADDRESS1, ip_addr_shoudong);
	
}


BEGIN_MESSAGE_MAP(IDD_SEARCHDlg, CDialogEx)
	ON_BN_CLICKED(B_SEARCH_1, &IDD_SEARCHDlg::OnBnClickedSearch1)
	ON_BN_CLICKED(IDOK, &IDD_SEARCHDlg::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &IDD_SEARCHDlg::OnLvnItemchangedList2)
	ON_BN_CLICKED(B_SEARCH_SETIP, &IDD_SEARCHDlg::OnBnClickedSearchSetip)
	ON_BN_CLICKED(IDC_BUTTON1, &IDD_SEARCHDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &IDD_SEARCHDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


BOOL IDD_SEARCHDlg::OnInitDialog(){
	CDialogEx::OnInitDialog();

	LANGID langid = GetSystemDefaultLangID();
	DWORD dwSytle=::GetWindowLong(m_ctrlDetectList.m_hWnd,GWL_STYLE); 
	SetWindowLong(m_ctrlDetectList.m_hWnd,GWL_STYLE,dwSytle|LVS_REPORT);
	DWORD ExStyle=m_ctrlDetectList.GetExtendedStyle();
	m_ctrlDetectList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_NUMBER,(LPCTSTR)"index",LVCFMT_CENTER,20);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_TYPE,(LPCTSTR)"type",LVCFMT_CENTER,40);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_NAME,(LPCTSTR)"name",LVCFMT_CENTER,60);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_IP,(LPCTSTR)"ip",LVCFMT_CENTER,100);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_NETMASK,(LPCTSTR)"netmask",LVCFMT_CENTER,100);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_GATEWAY,(LPCTSTR)"gateway",LVCFMT_CENTER,100);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_MAC,(LPCTSTR)"mac",LVCFMT_CENTER,160);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_PORT,(LPCTSTR)"version",LVCFMT_CENTER,80);
	m_ctrlDetectList.InsertColumn(LIST_COMLUMN_ESEE_ID,(LPCTSTR)"eseeid",LVCFMT_CENTER,100);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_DEVICE_ID,(LPCTSTR)"deviceid",LVCFMT_CENTER,280);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_MANUFATURER,(LPCTSTR)"manufacturer",LVCFMT_CENTER,280);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_PWD_TYPE,(LPCTSTR)"PWD_TYPE",LVCFMT_CENTER,280);
	g_index =0;
	stopSearch = true;

	stJASDK_Search_Init init ={0};
	init.local_ip ="192.168.1.81";
//	init.broadcast_ip ="192.168.255.255";
	init.search_proc.search_handle =  (notify_Search_Handle)search_notifyItemData;
//	init.search_proc.setip_handle = (notify_SetIP_Handle)search_notifySetIP;
//	init.search_proc.hb_handle = (notify_Hello_Bye_Handle)search_notifyHelloBye;
	init.pUser = this;
	handler = JASDK_Search_init(&init);
	printf("\r\n liry handler %d \r\n",handler);

	//删除搜索缓存列表
	while(first){
		LPSEARCHDATA tmp_data = first;
		first = first->next;
		if(tmp_data){
			if(tmp_data->item){
				memset(tmp_data->item,0,sizeof(STSEARCHDATA));
				free(tmp_data->item);
			}
			tmp_data->item = NULL;
			tmp_data->next = NULL;
			free(tmp_data);
			tmp_data = NULL;
		}
	}


	return true;
}
// IDD_SEARCHDlg 消息处理程序


void IDD_SEARCHDlg::OnBnClickedSearch1()
{
//	if(stopSearch){
		g_index =0;
//		stopSearch = false;
		m_ctrlDetectList.DeleteAllItems();
		int ret = JASDK_Search_Start(handler,JASDK_ALL,NULL,1);
		if(ret == 0){
			MessageBox("搜索完毕");
		}else{			
			MessageBox("搜索错误，请等1分钟后在试一下");
		}
//		m_cbSearch.SetWindowTextA((LPCTSTR)"停  止");
//		SetTimer(1, 2000, NULL);
//}else{
//		stopSearch = true;
//	JASDK_Search_Stop(handler);
//		m_cbSearch.SetWindowTextA((LPCTSTR)"搜  索");
		
//		KillTimer(1);
//	}
}


void IDD_SEARCHDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	JASDK_Search_destroy(handler);
	CWnd::ShowWindow(SW_HIDE);
	if(this->demodlg){
		POSITION hPos;
		int item;
		hPos = m_ctrlDetectList.GetFirstSelectedItemPosition();
		item = m_ctrlDetectList.GetNextSelectedItem(hPos);
	
		if(-1 <= item){
			CString device_id = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_DEVICE_ID);		
			CString device_name = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_NAME);
			CString device_IP = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_IP);
			CString esee_id = m_ctrlDetectList.GetItemText(item, LIST_COMLUMN_ESEE_ID);
			CString device_port = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_PORT);
			
			LPSEARCHDATA tmp_s = first;
			while(tmp_s){ //搜索链表和当前的ip
				if((strcmp(device_IP,tmp_s->item->ip) ==0 )||((strlen(esee_id)>5) && (strcmp(esee_id,tmp_s->item->esee_id) == 0))){
					((CJASDK_demoDlg*)demodlg)->setSearchInfo(tmp_s->item);
					break;
				}
				tmp_s = tmp_s->next;
			}
		}
	}

	CDialogEx::OnOK();
}


void IDD_SEARCHDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	POSITION hPos;
	int item;
	hPos = m_ctrlDetectList.GetFirstSelectedItemPosition();
	item = m_ctrlDetectList.GetNextSelectedItem(hPos);
	CString device_type = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_TYPE);
	if(strcmp(device_type,"IPCAM") != 0){
		return ;
	}
	if(-1 != item){
		
		CString device_id = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_DEVICE_ID);		
		CString device_name = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_NAME);
		CString device_IP = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_IP);
		CString device_netmask = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_NETMASK);
		CString device_gateway = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_GATEWAY);
		CString device_port = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_PORT);
		strcpy(st_info.device_gateway ,device_gateway);
		strcpy(st_info.device_id ,device_id);
		strcpy(st_info.device_name ,device_name);
		strcpy(st_info.device_ip ,device_IP);
		strcpy(st_info.device_netmask ,device_netmask);
		strcpy(st_info.http_port ,device_port);	
		ip_addr_edit.SetWindowTextA(st_info.device_ip);
		netmask_edit.SetWindowTextA(st_info.device_netmask);
		gateway_edit.SetWindowTextA(st_info.device_gateway);
		port_edit.SetWindowTextA(st_info.http_port);
	}
}



void IDD_SEARCHDlg::OnBnClickedSearchSetip()
{
	// TODO: 在此添加控件通知处理程序代码
	memset(&st_info_new,0,sizeof(st_info_new));
	strcpy(st_info_new.device_id , st_info.device_id);
	strcpy(st_info_new.device_name , st_info.device_name);
	st_info_new.device_password_type = st_info.device_password_type;
	ip_addr_edit.GetWindowTextA(st_info_new.device_ip,16);
	netmask_edit.GetWindowTextA(st_info_new.device_netmask,16);
	gateway_edit.GetWindowTextA(st_info_new.device_gateway,16);
	port_edit.GetWindowTextA(st_info_new.device_mac,18);
	username_edit.GetWindowTextA(st_info_new.device_username,32); 
	password_edit.GetWindowTextA(st_info_new.device_password,32);
	st_info_new.device_password_type = PWD_TYPE_MD5;
	if(strlen(st_info_new.device_username)>0 ){
		JASDK_SetupIP(handler,st_info_new);
	}

}

void IDD_SEARCHDlg::setCJASDK_demoDlg(void* demodlg){
	this->demodlg = (void*)demodlg;
}


void IDD_SEARCHDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	JASDK_Search_destroy(handler);
	CWnd::ShowWindow(SW_HIDE);
	stJASDKSearchItem item;
	memset(&item,0,sizeof(stJASDKSearchItem));	
	ip_addr_shoudong.GetWindowTextA(item.ip,16);
	strcpy(item.ch_num,"1");
	strcpy(item.port,"80");
	strcpy(item.device_model,"IPCAM");
	((CJASDK_demoDlg*)demodlg)->setSearchInfo(&item);
	CDialogEx::OnOK();
}

void IDD_SEARCHDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	JASDK_Search_destroy(handler);
	if(this->demodlg){
		POSITION hPos;
		int item;
		hPos = m_ctrlDetectList.GetFirstSelectedItemPosition();
		item = m_ctrlDetectList.GetNextSelectedItem(hPos);

		if(-1 <= item){
			CString device_id = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_DEVICE_ID);		
			CString device_name = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_NAME);
			CString device_IP = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_IP);
			CString esee_id = m_ctrlDetectList.GetItemText(item, LIST_COMLUMN_ESEE_ID);
			CString device_port = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_PORT);
			LPSEARCHDATA tmp_s = first;
			while(tmp_s){ //搜索链表和当前的ip
				if((strcmp(device_IP,tmp_s->item->ip) ==0 )||((strlen(esee_id)>5) && (strcmp(esee_id,tmp_s->item->esee_id) == 0))){
					CWnd::ShowWindow(SW_HIDE);
					((CJASDK_demoDlg*)demodlg)->setSearchInfo(tmp_s->item);
					break;
				}
				tmp_s = tmp_s->next;
			}

		}
	}

	CDialogEx::OnOK();
	*pResult = 0;
}