// PlayBackDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JASDK_demo.h"
#include "PlayBackDlg.h"
#include "afxdialogex.h"
#include "JASDK_demoDlg.h"

#define LIST_COLUMN_NUMBER (0)
#define LIST_COLUMN_TYPE (1)
#define LIST_COLUMN_CHN (2)
#define LIST_COLUMN_STARTTIME (3)
#define LIST_COLUMN_STOPTIME (4)

// CPlayBackDlg 对话框

const void demo_PlayBackCallBack(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser){
	 ((CPlayBackDlg*)dwUser)->callBack(lPlayHandle, dwDataType,pBuffer,dwBufSize);

}

int calLocalTime(LPJASDK_PLAYBACK_TIME srcTime,LPJASDK_PLAYBACK_TIME dstTime){
	if(NULL == srcTime || (NULL == dstTime)){
		return 0;
	}
	struct tm srctm,*dsttm;
	memset(&srctm,0,sizeof(struct tm));

	srctm.tm_year = srcTime->dwYear;
	srctm.tm_mon = srcTime->dwMonth;
	srctm.tm_mday = srcTime->dwDay;
	srctm.tm_hour = srcTime->dwHour;
	srctm.tm_min = srcTime->dwMinute;
	srctm.tm_sec = srcTime->dwMinute;
	time_t srcit = mktime(&srctm);
	srcit += 3600*8;
	dsttm = gmtime(&srcit);
	dstTime->dwYear = dsttm->tm_year;
	dstTime->dwMonth = dsttm->tm_mon;
	dstTime->dwDay = dsttm->tm_mday;
	dstTime->dwHour = dsttm->tm_hour;
	dstTime->dwMinute = dsttm->tm_min;
	dstTime->dwSecond = dsttm->tm_sec;
	return 1;
}

IMPLEMENT_DYNAMIC(CPlayBackDlg, CDialogEx)

CPlayBackDlg::CPlayBackDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPlayBackDlg::IDD, pParent)
{

}

CPlayBackDlg::~CPlayBackDlg()
{
}

void CPlayBackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, D_m_dateCtrlstart);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, D_m_dateCtrlstop);
	DDX_Control(pDX, IDC_PLAYBACKSEARCH, B_playBackSearch);
	DDX_Control(pDX, IDC_PLAYBACKLIST, m_ctrlDetectList);
	DDX_Control(pDX, IDC_PB_PLAY, pbPlay);
}

BOOL CPlayBackDlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	D_m_dateCtrlstart.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	D_m_dateCtrlstop.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	CTime TimeTemp=TimeTemp.GetCurrentTime();
	D_m_dateCtrlstart.SetTime(&TimeTemp);
	D_m_dateCtrlstop.SetTime(&TimeTemp);
	pbSearchHandle = 0;
	LANGID langid = GetSystemDefaultLangID();
	DWORD dwSytle=::GetWindowLong(m_ctrlDetectList.m_hWnd,GWL_STYLE); 
	SetWindowLong(m_ctrlDetectList.m_hWnd,GWL_STYLE,dwSytle|LVS_REPORT);
	DWORD ExStyle=m_ctrlDetectList.GetExtendedStyle();
	m_ctrlDetectList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_NUMBER,(LPCTSTR)"index",LVCFMT_CENTER,20);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_TYPE,(LPCTSTR)"type",LVCFMT_CENTER,40);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_CHN,(LPCTSTR)"channel",LVCFMT_CENTER,40);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_STARTTIME,(LPCTSTR)"starttime",LVCFMT_CENTER,40);
	m_ctrlDetectList.InsertColumn(LIST_COLUMN_STOPTIME,(LPCTSTR)"stoptime",LVCFMT_CENTER,40);
	g_index =0;
	i_num = 0;
	b_pb_play = false;
	pbPlayHandle = 0;
	downloadFile = false;
	PBDownloadFile = NULL;
	PBDownloadCallBack = NULL;
	fpcall = NULL;
	PlaybackWnd = GetDlgItem(IDC_PLAYBACK_VIEW)->GetSafeHwnd();
	return TRUE;
}


BEGIN_MESSAGE_MAP(CPlayBackDlg, CDialogEx)
	ON_BN_CLICKED(IDC_PLAYBACKSEARCH, &CPlayBackDlg::OnBnClickedPlaybacksearch)
	ON_BN_CLICKED(IDC_PB_PLAY, &CPlayBackDlg::OnBnClickedPbPlay)
	ON_BN_CLICKED(IDC_PB_PAUSE, &CPlayBackDlg::OnBnClickedPbPause)
	ON_BN_CLICKED(IDC_PB_PLAY_PLAY, &CPlayBackDlg::OnBnClickedPbPlayPlay)
	ON_BN_CLICKED(IDC_BUTTON1, &CPlayBackDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPlayBackDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPlayBackDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDOK, &CPlayBackDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPlayBackDlg 消息处理程序


void CPlayBackDlg::OnBnClickedPlaybacksearch()
{
	// TODO: 在此添加控件通知处理程序代码

	CTime t_start,t_stop;
	STJASDK_PLAYBACK_TIME starttime;
	STJASDK_PLAYBACK_TIME stoptime;
	D_m_dateCtrlstart.GetTime(t_start);
	
	starttime.dwYear = t_start.GetYear();
	starttime.dwMonth = t_start.GetMonth();	
	starttime.dwDay = t_start.GetDay();
	starttime.dwHour = t_start.GetHour();
	starttime.dwMinute = t_start.GetMinute();
	starttime.dwSecond = t_start.GetSecond();

	

	D_m_dateCtrlstop.GetTime(t_stop);
	stoptime.dwYear = t_stop.GetYear();
	stoptime.dwMonth = t_stop.GetMonth();
	stoptime.dwDay = t_stop.GetDay();
	stoptime.dwHour = t_stop.GetHour();
	stoptime.dwMinute = t_stop.GetMinute();
	stoptime.dwSecond = t_stop.GetSecond();

	if(pbSearchHandle){
		JASDK_PLAYBACK_FindClose(pbSearchHandle);
		pbSearchHandle = NULL;
	}

	pbSearchHandle = JASDK_PLAYBACK_FindFile(lUserID,0,0x0f,&starttime,&stoptime);
	if(pbSearchHandle){
		while(1){
			STJASDK_FIND_DATA data;
			int ret = JASDK_PLAYBACK_FindNextFile(pbSearchHandle,&data);
			if(JASDK_PLAYBACK_FILE_SUCCESS != ret){
				break;
			}

			char str_number[16];
			memset(str_number, 0, sizeof(str_number));
			_snprintf(str_number, sizeof(str_number), "%d", g_index+1);
			m_ctrlDetectList.InsertItem(g_index, (LPCTSTR)str_number);
			m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_NUMBER, LPCTSTR(str_number));
			char type1[8];
			itoa(data.type,(char*)&type1,10);
			m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_TYPE, LPCTSTR(type1));
			char chn1[8];
			itoa(data.nChannel,(char*)&chn1,10);
			m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_CHN, LPCTSTR(chn1));
			{
			char starttime[64];
			_snprintf(starttime,sizeof(starttime),"%d年%d月%d日%d时%d分%d秒",data.struStartTime.dwYear,
				data.struStartTime.dwMonth,data.struStartTime.dwDay,data.struStartTime.dwHour,
				data.struStartTime.dwMinute,data.struStartTime.dwSecond);
				m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_STARTTIME, (LPCTSTR)starttime);
			}
			{
			char stoptime[64];
			_snprintf(stoptime,sizeof(stoptime),"%d年%d月%d日%d时%d分%d秒",data.struStopTime.dwYear,
				data.struStopTime.dwMonth,data.struStopTime.dwDay,data.struStopTime.dwHour,
				data.struStopTime.dwMinute,data.struStopTime.dwSecond);
			m_ctrlDetectList.SetItemText(g_index, LIST_COLUMN_STOPTIME, (LPCTSTR)stoptime);
			}
			g_index ++;
		
		}
		JASDK_PLAYBACK_FindClose(pbSearchHandle);
		pbSearchHandle = NULL;
	}

}


void CPlayBackDlg::setCJASDK_demoDlg(void* sdkd,int userid){
	JASDK_demo = sdkd;
	lUserID = userid;
}

void CPlayBackDlg::OnBnClickedPbPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	if(b_pb_play){
		b_pb_play = false;
		JASDK_StopPlayBack(pbPlayHandle);
		pbPlay.SetWindowTextA(_T("播  放"));
		pbPlayHandle = NULL;
	
	}else{
		POSITION hPos;
		int item;
		hPos = m_ctrlDetectList.GetFirstSelectedItemPosition();
		item = m_ctrlDetectList.GetNextSelectedItem(hPos);
		if(-1 <= item){
			CString device_type = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_TYPE);		
			CString device_chn = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_CHN);
			CString device_startTime = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_STARTTIME);
			CString device_stopTime = m_ctrlDetectList.GetItemText(item, LIST_COLUMN_STOPTIME);
	
			
			HWND hwnd =  GetDlgItem(IDC_PLAYBACK_VIEW)->GetSafeHwnd();

			STJASDK_PLAYBACK_TIME startTime;
			memset(&startTime,0,sizeof(STJASDK_PLAYBACK_TIME));
			sscanf(device_startTime,"%d年%d月%d日%d时%d分%d秒",&startTime.dwYear,&startTime.dwMonth,&startTime.dwDay,&startTime.dwHour,&startTime.dwMinute,&startTime.dwSecond);
			STJASDK_PLAYBACK_TIME stopTime;
			memset(&stopTime,0,sizeof(STJASDK_PLAYBACK_TIME));
			sscanf(device_stopTime,"%d年%d月%d日%d时%d分%d秒",&stopTime.dwYear,&stopTime.dwMonth,&stopTime.dwDay,&stopTime.dwHour,&stopTime.dwMinute,&stopTime.dwSecond);

//			calLocalTime(&startTime,&gmtStartTime);
//			calLocalTime(&stopTime,&gmtStopTime);
			//视频播放
			pbPlayHandle = JASDK_PlayBackByTime(lUserID,atoi(device_chn), &startTime, &stopTime, PlaybackWnd);
//			pbPlayHandle = JASDK_PLAYBACK_FindFile(lUserID,atoi(device_chn),atoi(device_type),&startTime,&stopTime);
			if(pbPlayHandle){
				JASDK_PlayBackControl(pbPlayHandle,JASDK_PLAYBACK_PLAYSTART,0,0);
			}
			pbPlay.SetWindowTextA(_T("停 止"));
			b_pb_play = true;
			
		}
	}


}


void CPlayBackDlg::OnBnClickedPbPause()
{
	// TODO: 在此添加控件通知处理程序代码
	if(true == b_pb_play){
		BOOL ret = JASDK_PlayBackControl(pbPlayHandle,JASDK_PLAYBACK_PLAYPAUSE,0,0);
		if(ret == TRUE){
			printf("set pause success \n");
		}else {
			printf("set pause failure \n");
		}
	}
}


void CPlayBackDlg::OnBnClickedPbPlayPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	if(true == b_pb_play){
		BOOL ret = JASDK_PlayBackControl(pbPlayHandle,JASDK_PLAYBACK_PLAYRESTART,0,0);
		if(ret == TRUE){
			printf("set pause success \n");
		}else {
			printf("set pause failure \n");
		}
	}
}


void CPlayBackDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//抓图
	i_num++;
	char savePicPath[64];
	memset(savePicPath,0,sizeof(savePicPath));
	_snprintf(savePicPath,64,"D:\\huifangzhuatu%d.bmp",i_num);
	BOOL ret = JASDK_PlayBackCaptureFile(pbPlayHandle,savePicPath);
}


void CPlayBackDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//下载
	if(downloadFile == false){
	CTime t_start,t_stop;
	STJASDK_PLAYBACK_TIME starttime;
	STJASDK_PLAYBACK_TIME stoptime;
	D_m_dateCtrlstart.GetTime(t_start);
	starttime.dwYear = t_start.GetYear();
	starttime.dwMonth = t_start.GetMonth();
	starttime.dwDay = t_start.GetDay();
	starttime.dwHour = t_start.GetHour();
	starttime.dwMinute = t_start.GetMinute();
	starttime.dwSecond = t_start.GetSecond();

	D_m_dateCtrlstop.GetTime(t_stop);
	stoptime.dwYear = t_stop.GetYear();
	stoptime.dwMonth = t_stop.GetMonth();
	stoptime.dwDay = t_stop.GetDay();
	stoptime.dwHour = t_stop.GetHour();
	stoptime.dwMinute = t_stop.GetMinute();
	stoptime.dwSecond = t_stop.GetSecond();

	i_num++;
	char savePicPath[64];
	memset(savePicPath,0,sizeof(savePicPath));
	_snprintf(savePicPath,64,"D:\\download%d.h264",i_num);
	PBDownloadFile = JASDK_PlayBack_GetFileByTime(lUserID, 0,&starttime,&stoptime, savePicPath);
	downloadFile = true;
	if(PBDownloadFile){
		//开始录像
		MessageBox(" 开始录像");
	}
	}else{
		JASDK_PlayBack_StopGetFile(PBDownloadFile);
		MessageBox(" 停止录像");
		downloadFile = false;
	}
	
}


void CPlayBackDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(b_pb_play == true){
		JASDK_PlayBack_SetPlayDataCallBack(pbPlayHandle,(fPlayDataCallBack)demo_PlayBackCallBack,(DWORD)this);
		
		if(fpcall){
			fclose(fpcall);
			fpcall = NULL;
		}
		char callbackPath[64] = {"D:\\pbcallback.h264"};
//		remove(callbackPath);
		fpcall = fopen(callbackPath,"wb+");
		if(fpcall){
			MessageBox(" 回调开始录像");
		}else{
			MessageBox(" 回调打开文件失败");
		}	
	}else{
		if(fpcall){
			fclose(fpcall);
			fpcall = NULL;
		}

	}
}

void CPlayBackDlg::callBack(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize){
	if(pBuffer == NULL || dwBufSize<=0){
		return ;
	}
	if(fpcall){
		fwrite(pBuffer,dwBufSize,1,fpcall);	
		fflush(fpcall);
	}

}

void CPlayBackDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	JASDK_StopPlayBack(pbPlayHandle);
	JASDK_PlayBack_StopGetFile(PBDownloadFile);
	if(fpcall){
		fclose(fpcall);
	}
//	((CJASDK_demoDlg*)JASDK_demo)->restartRealPlay();
	CDialogEx::OnOK();
}
