
// JASDK_demoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JASDK_demo.h"
#include "JASDK_demoDlg.h"
#include "afxdialogex.h"
#include "JASDK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


const void notify_ExceptionMessage(LONG lUserID,LONG lHandle,DWORD dwType,DWORD exNum,void *pUser){
	((CJASDK_demoDlg*)pUser)->sdknotify_ExceptionMessage(lUserID, lHandle,dwType,exNum,pUser);
}

// CJASDK_demoDlg 对话框
void InitConsoleWindow()
{
    int nCrt = 0;
    FILE* fp;
    AllocConsole();
    nCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
    fp = _fdopen(nCrt, "w");
    *stdout = *fp;
    setvbuf(stdout, NULL, _IONBF, 0);
}



CJASDK_demoDlg::CJASDK_demoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJASDK_demoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	InitConsoleWindow();
//	i_num =0;

}

void CJASDK_demoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,B_LUXIANG,b_luxiang_l);

}

BEGIN_MESSAGE_MAP(CJASDK_demoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(SEARCH_DEVICE, &CJASDK_demoDlg::OnBnClickedDevice)
	ON_BN_CLICKED(B_SET_CONFIG, &CJASDK_demoDlg::OnBnClickedSetConfig)
	ON_BN_CLICKED(IDOK, &CJASDK_demoDlg::OnBnClickedOk)
	ON_BN_CLICKED(B_LUXIANG, &CJASDK_demoDlg::OnBnClickedLuxiang)
	ON_BN_CLICKED(B_HUIFANG, &CJASDK_demoDlg::OnBnClickedHuifang)
	ON_BN_CLICKED(B_ZHUATU, &CJASDK_demoDlg::OnBnClickedZhuatu)
	ON_BN_CLICKED(IDCANCEL, &CJASDK_demoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CJASDK_demoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_STOPREAL, &CJASDK_demoDlg::OnBnClickedStopreal)
	ON_BN_CLICKED(IDC_REALPLAY, &CJASDK_demoDlg::OnBnClickedRealplay)
	ON_BN_CLICKED(B_YUNTAI, &CJASDK_demoDlg::OnBnClickedYuntai)
END_MESSAGE_MAP()


// CJASDK_demoDlg 消息处理程序

BOOL CJASDK_demoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	memset(this->filepath1,0,255);
	int lens = sizeof(filepath2);
	memset(filepath2,0,sizeof(filepath2));
	b_savefile1 = false;
	b_savefile2 = false;
	b_savefile_avi = false;
		i_num =0;
		curnum =0;
	JASDK_Init();
	JASDK_SetSDKMessage((fExceptionCallBack)notify_ExceptionMessage,this);
	memset(userId,0,sizeof(userId));
	memset(RealPlay_handle,0,sizeof(RealPlay_handle));
	fp = NULL;
	char version[64] = {0};
	_snprintf(version,sizeof(version)," JASDK %s",JASDK_GetSDKVersion());

	GetDlgItem(IDC_VERSION_STATIC)->SetWindowText(version);
	GetDlgItem(IDC_DEVIP)->SetWindowText("IP:");
	GetDlgItem(IDC_CZSM)->SetWindowText("首先搜索设备，先点击“搜素设备”按钮，弹出搜索窗口，点击“搜索”按钮，搜索出设备列表，选中需要显示的设备，双击就可以了。\
目前只有：“搜索设备”，“回放”，“录像”，“抓图”可以使用\
“录像”和“抓图”按钮只有在视频播放时才有效\
回放窗口,只能搜索开始的当天的录像视频，播放视频时，不能下载，下载不能播放。回放播放时才能抓图。");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CJASDK_demoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CJASDK_demoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CJASDK_demoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CJASDK_demoDlg::OnBnClickedDevice()
{
	int i =0;
	for(i = 0;i<4;i++){
//		JASDK_StopRealPlay(RealPlay_handle[i]);
		JASDK_Logout(userId[i]);
		userId[i] = NULL;
		RealPlay_handle[i] = NULL;
	}
	searchDlg.setCJASDK_demoDlg(this);
	searchDlg.DoModal();
}
int ipc_num =0;
struct thread_login{
	void* thiz;
	pstJASDKSearchItem info;
	int num;
};
void test_thread_process_login(void *argv);
void CJASDK_demoDlg::setSearchInfo(pstJASDKSearchItem info){
	if(NULL == info){
		return ;
	}
//	stJASDKSearchItem stinfo = {0};
//	info = &stinfo;
//	strcpy(info->device_model,"IPCAM");
	if((strlen(info->ip) > 0) || (strlen(info->esee_id) > 0)){
	
		//密码输入框，输入密码
		memset(username,0,sizeof(username));
		memset(password,0,sizeof(password));
		userPwdDlg.setDemoDlg((void*)this);
		userPwdDlg.DoModal();
		//如果已经有了视频预览，先删除
		int i;
//		for( i=0; i < DISPLAY_NUM; i++){
//			if(NULL != userId[i]){
//				JASDK_StopRealPlay(RealPlay_handle[i]);
//				JASDK_Logout(userId[i]);
//				userId[i] = NULL;
//				RealPlay_handle[i] = NULL;
//			}
//		}
		
		//视频预览,IPC
		if((strcmp(info->device_model,"IPCAM") ==0) || (strcmp(info->device_model,"IPC") ==0)){
			//注册，验证密码
			userId[ipc_num] = JASDK_Login(info->ip,atoi(info->port), strlen(username)>0?username:NULL,strlen(password)>0?password:NULL,GMT_E8);
//			userId[ipc_num] = JASDK_Login_EseeId("545413455","admin",NULL,GMT_E8);
			if(0 == userId[ipc_num]){
				printf("error :%d \r\n",JASDK_GetLastError());
				int errnologin = (int)JASDK_GetLastError();
				switch(errnologin){
				case JASDK_NETWORK_FAIL_CONNECT:
					MessageBox("连接错误");
					break;
				case JASDK_PASSWORD_ERROR:
					MessageBox("用户名或密码错误");
					break;
				case JASDK_MEMORY_ERROR:
					MessageBox("内存错误");
					break;
				case JASDK_PARAMETER_ERROR:
					MessageBox("参数错误");
					break;
				}				
				return ;
			}

			STJASDK_CLIENTINFO clientInfo;
			memset(&clientInfo,0 ,sizeof(clientInfo));
			clientInfo.Channel = 0;
			clientInfo.Stream = 0;
			clientInfo.PlayWnd = GetDlgItem(E_STATIC_PIC_1)->GetSafeHwnd();
			RealPlay_handle[ipc_num] = JASDK_RealPlay(userId[ipc_num],&clientInfo);
//			ipc_num++;
			if(ipc_num >=3){
				ipc_num =3;
			}
		}else {
			//nvr
			int i =0;
			int chnum = atoi(info->ch_num);
			int num = chnum >1 ?chnum : 1;
			num = num > 4 ? 4:num;
			printf("JASDK_demoDlg.cpp setSearchInfo portnum %d\n",num);
/*
			for(i =0;i<4;i++){
				curnum = i;

				HANDLE hThreadTemp;
				DWORD dwThreadId;
				struct thread_login login_thread;
				login_thread.thiz = this;
				login_thread.info = info;
				login_thread.num = i;
				hThreadTemp = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)test_thread_process_login,&login_thread,0,&dwThreadId);
				if (NULL == hThreadTemp)
				{
					continue;;
				}
	;
			}
*/


				userId[i] = JASDK_Login_EseeId(info->esee_id,strlen(username)>0?username:NULL,strlen(password)>0?password:NULL,GMT_E8);
//				userId[i] = JASDK_Login(info->ip,atoi(info->port), strlen(username)>0?username:NULL,strlen(password)>0?password:NULL,GMT_E8);
				if(0 == userId[i]){
					printf("error :%d \r\n",JASDK_GetLastError());
					int errnologin = (int)JASDK_GetLastError();
					switch(errnologin){
					case JASDK_NETWORK_FAIL_CONNECT:
						MessageBox("连接错误");
						break;
					case JASDK_PASSWORD_ERROR:
						MessageBox("用户名或密码错误");
						break;
					case JASDK_MEMORY_ERROR:
						MessageBox("内存错误");
						break;
					case JASDK_PARAMETER_ERROR:
						MessageBox("参数错误");
						break;;
					}
	//				 continue;
					return ;
				}

				int number = JASDK_getChannelCount(userId[i]);

					STJASDK_CLIENTINFO clientInfo;
					memset(&clientInfo,0 ,sizeof(clientInfo));
					clientInfo.Channel = i;
					clientInfo.Stream = 0;
					switch(i){
					case 0:
						clientInfo.PlayWnd =  GetDlgItem(E_STATIC_PIC_1)->GetSafeHwnd();
						break;
					case 1:
						clientInfo.PlayWnd =  GetDlgItem(E_STATIC_PIC_2)->GetSafeHwnd();
						break;
					case 2:
						clientInfo.PlayWnd =  GetDlgItem(E_STATIC_PIC_3)->GetSafeHwnd();
						break;
					case 3:
						clientInfo.PlayWnd =  GetDlgItem(E_STATIC_PIC_4)->GetSafeHwnd();
						break;
					default:
						clientInfo.PlayWnd =  GetDlgItem(E_STATIC_PIC_1)->GetSafeHwnd();
						break;

					}				
					RealPlay_handle[i] = JASDK_RealPlay(userId[i],&clientInfo);
//			}

		}
		if(strlen(info->ip)>5){
			char ipstatic[256] ={0};
			sprintf(ipstatic,"IP: %s",info->ip);
			GetDlgItem(IDC_DEVIP)->SetWindowText(ipstatic);
		}else{
			GetDlgItem(IDC_DEVIP)->SetWindowText("IP:");

		}
	}

}
void test_thread_process_login(void *argv){
	struct thread_login* arg = (struct thread_login*)argv;
	((CJASDK_demoDlg*)(arg->thiz))->thread_process_login(arg->info,arg->num);
}

int curnum1 =0;
void CJASDK_demoDlg::thread_process_login(pstJASDKSearchItem info,int thread){
	JASDK_StopRealPlay(userId[thread]);
	userId[thread] = NULL;
	userId[thread] = JASDK_Login_EseeId(info->esee_id,strlen(username)>0?username:NULL,strlen(password)>0?password:NULL,GMT_E8);
	//				userId[i] = JASDK_Login(info->ip,atoi(info->port), strlen(username)>0?username:NULL,strlen(password)>0?password:NULL,GMT_E8);
	userId[thread] = JASDK_Login_EseeId(info->esee_id,strlen(username)>0?username:NULL,strlen(password)>0?password:NULL,GMT_E8);
	int i = thread;
	if(0 == userId[i]){
		printf("error :%d \r\n",JASDK_GetLastError());
		int errnologin = (int)JASDK_GetLastError();
		switch(errnologin){
		case JASDK_NETWORK_FAIL_CONNECT:
			MessageBox("连接错误");
			break;
		case JASDK_PASSWORD_ERROR:
			MessageBox("用户名或密码错误");
			break;
		case JASDK_MEMORY_ERROR:
			MessageBox("内存错误");
			break;
		case JASDK_PARAMETER_ERROR:
			MessageBox("参数错误");
			break;;
		}
		//				 continue;
		return ;
	}


	STJASDK_CLIENTINFO clientInfo;
	memset(&clientInfo,0 ,sizeof(clientInfo));
	clientInfo.Channel = i;
	clientInfo.Stream = 1;
	switch(i){
	case 0:
		clientInfo.PlayWnd =  GetDlgItem(E_STATIC_PIC_1)->GetSafeHwnd();
		break;
	case 1:
		clientInfo.PlayWnd =  GetDlgItem(E_STATIC_PIC_2)->GetSafeHwnd();
		break;
	case 2:
		clientInfo.PlayWnd =  GetDlgItem(E_STATIC_PIC_3)->GetSafeHwnd();
		break;
	case 3:
		clientInfo.PlayWnd =  GetDlgItem(E_STATIC_PIC_4)->GetSafeHwnd();
		break;
	default:
		clientInfo.PlayWnd =  GetDlgItem(E_STATIC_PIC_1)->GetSafeHwnd();
		break;

	}				
	RealPlay_handle[i] = JASDK_RealPlay(userId[i],&clientInfo);

//	curnum++;
}


void CJASDK_demoDlg::OnBnClickedSetConfig()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CJASDK_demoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	for( i=0; i < DISPLAY_NUM; i++){
		if(NULL != userId[i]){
			JASDK_Logout(userId[i]);
			userId[i] = NULL;
		}
	}


	CDialogEx::OnOK();
}


void CJASDK_demoDlg::OnBnClickedLuxiang()
{
	// TODO: 在此添加控件通知处理程序代码
/*	if(b_savefile1 == false)
		saveFileDlg.setSavePath((void*)this,1,NULL,false);
	else 
		saveFileDlg.setSavePath((void*)this,1,filepath1,true);
	if(b_savefile2 == false)
		saveFileDlg.setSavePath((void*)this,2,NULL,false);
	else 
		saveFileDlg.setSavePath((void*)this,2,filepath2,true);
	saveFileDlg.DoModal();
*/
	i_num ++;
	//数据回调
/*
	if(b_savefile1 == false){
		char lpszStringBuf[64]={0};
		_snprintf(lpszStringBuf,64,"d:\\realPlayCallback%d.h264",i_num);
		saveFile1(lpszStringBuf,strlen(lpszStringBuf),1);
		char bufpuzhuo[128]={0};
		_snprintf(bufpuzhuo,128,"数据捕捉：保存文件到D盘:%s",lpszStringBuf);
		MessageBox(bufpuzhuo);
	}else{
		char lpszStringBuf[64]={0};
		saveFile1(lpszStringBuf,strlen(lpszStringBuf),0);
		MessageBox("数据取消捕捉");
	}
	//数据保存文件
	if(b_savefile2 == false){
		char lpszStringBuf1[64]={0};
		_snprintf(lpszStringBuf1,64,"d:\\saveFile%d.h264",i_num);
		saveFile2(lpszStringBuf1,strlen(lpszStringBuf1),1);	
	}else{
		char lpszStringBuf1[64]={0};
		saveFile2(lpszStringBuf1,strlen(lpszStringBuf1),0);
	}*/
	if(b_savefile_avi == false){
		char lpszStringBuf1[64]={0};
		_snprintf(lpszStringBuf1,64,"d:\\saveFileavi%d.avi",i_num);
		saveFile_avi(lpszStringBuf1,strlen(lpszStringBuf1),1);	
	}else{
		char lpszStringBuf1[64]={0};
		saveFile_avi(lpszStringBuf1,strlen(lpszStringBuf1),0);
	}
	
	//数据保存文件
/*	if(b_savefile2 == false){
		char lpszStringBuf1[64]={0};
		_snprintf(lpszStringBuf1,64,"d:\\saveFile%d.h264",i_num);
		saveFile2(lpszStringBuf1,strlen(lpszStringBuf1),1);	
	}else{
		char lpszStringBuf1[64]={0};
		saveFile2(lpszStringBuf1,strlen(lpszStringBuf1),0);
	}
	*/
}

const void demo_RealDataCallBack(LONG lRealHandle, DWORD dwDataType,BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser){
	 ((CJASDK_demoDlg*)dwUser)->notifyData(lRealHandle, dwDataType,pBuffer,dwBufSize);

}


void CJASDK_demoDlg::saveFile1(char* path1,int length,int flag){
	//这里只为 JASDK_SetRealDataCallBack，fRealDataCallBack 调用示例，直接保存到文件里面了。
	if(flag ==0){ //
		if(fp){
			fclose(fp);
		}
		b_savefile1 = false;
		JASDK_SetRealDataCallBack(RealPlay_handle[0],(fRealDataCallBack)NULL, (DWORD)NULL);
	}else {
		if((strlen(path1) >0 && (strlen(path1)<256) )&& (length >0)){
			int ret = JASDK_SetRealDataCallBack(RealPlay_handle[0],(fRealDataCallBack)demo_RealDataCallBack, (DWORD)this);
			if(ret == 0){ //错误了
				b_savefile1 = false;
				MessageBox("回调设置出错");
				return;
			}
			if(fp){
				fclose(fp);
				fp = NULL;
			}
			fp = fopen(path1,"wb+");
			if(NULL != fp){
				b_savefile1 = true;
				memset(filepath1,0,sizeof(filepath1));
				strcpy(filepath1,path1);
			}else{
				b_savefile1 = false;
				JASDK_SetRealDataCallBack(RealPlay_handle[0],NULL, (DWORD)NULL);
				char shibai[256] ={0};
				sprintf(shibai,"打开文件失败:%s",path1);
				MessageBox(shibai);
			}
		}
	}

}
void CJASDK_demoDlg::saveFile2(char* path2,int length,int flag){
	//这里只为  演示
	if(flag ==0 ){
		b_savefile2 = false;
		memset(filepath2,0,sizeof(filepath2));
		JASDK_StopSaveRealData(RealPlay_handle[0]);
		MessageBox("关闭实时录像");
		return;
	}

	//保存文件
	if(strlen(path2)<256){
		if(b_savefile2 == true){
			JASDK_StopSaveRealData(RealPlay_handle[0]);
			memset(filepath2,0,sizeof(filepath2));
			b_savefile2 = false;
		}

		bool ret = JASDK_SaveRealData(RealPlay_handle[0],path2);
		if(ret == true){
			b_savefile2 = true;
			memset(filepath2,0,sizeof(filepath2));
			strcpy(filepath2,path2);
		}else{

			b_savefile2 = false;
			MessageBox("实时录像设置失败");
		}
		
	}

	if(b_savefile2){
		char luxiangwenjian[128]={0};
		sprintf(luxiangwenjian,"实时录像，录像文件：%s",path2);
		MessageBox(luxiangwenjian);
//		b_luxiang_l.SetWindowTextA("正在录像");
	}else{
		MessageBox("关闭实时录像");
//		b_luxiang_l.SetWindowTextA("录像");
	}

}
#define WAVE_FORMAT_PCM                 (0x0001)
#define WAVE_FORMAT_ALAW                (0x0006)
void CJASDK_demoDlg::saveFile_avi(char* avipath,int length,int flag){
	if(flag ==0 ){
		b_savefile_avi = false;
		memset(filepath_avi,0,sizeof(filepath_avi));
		JASDK_StopSaveRealData_AVI(RealPlay_handle[0]);
		MessageBox("关闭实时录像");
		return;
	}

	//保存文件
	if(strlen(avipath)<256){
		if(b_savefile_avi == true){
			JASDK_StopSaveRealData_AVI(RealPlay_handle[0]);
			memset(filepath_avi,0,sizeof(filepath_avi));
			b_savefile_avi= false;
		}

		STAVI_SAVE_INFO aviinfo;
		memset(&aviinfo,0,sizeof(STAVI_SAVE_INFO));
		aviinfo.v_w = 1280;
		aviinfo.v_h = 960;
		aviinfo.v_fps = 15;
		strcpy(aviinfo.v_compressor, "X264");
		strcpy(aviinfo.filename,avipath);
		aviinfo.a_channels = 1;
		aviinfo.a_rate = 8000;
		aviinfo.a_bits = 16;
		aviinfo.a_format = WAVE_FORMAT_ALAW;
		bool ret = JASDK_SaveRealData_AVI(RealPlay_handle[0],&aviinfo);
		if(ret == true){
			b_savefile_avi = true;
			memset(filepath_avi,0,sizeof(filepath_avi));
			strcpy(filepath_avi,avipath);
		}else{
			b_savefile_avi = false;
			MessageBox("实时录像设置失败");
		}

	}

	if(b_savefile_avi){
		char luxiangwenjian[128]={0};
		sprintf(luxiangwenjian,"实时录像，录像文件：%s",filepath_avi);
		MessageBox(luxiangwenjian);
		//		b_luxiang_l.SetWindowTextA("正在录像");
	}else{
		MessageBox("关闭实时录像");
		//		b_luxiang_l.SetWindowTextA("录像");
	}

}

void CJASDK_demoDlg::notifyData(LONG lRealHandle, DWORD dwDataType,BYTE *pBuffer,DWORD dwBufSize){
	if(b_savefile1 ==false || fp ==NULL){
		return;
	}
	fseek(fp,0L,SEEK_END);
	fwrite(pBuffer,dwBufSize,1,fp);
	fflush(fp);
}

void CJASDK_demoDlg::OnBnClickedHuifang()
{
	// TODO: 在此添加控件通知处理程序代码
//	JASDK_StopRealPlay(RealPlay_handle[0]);
//	RealPlay_handle[0] = NULL;
	playBackDlg.setCJASDK_demoDlg(this,userId[0]);
	playBackDlg.DoModal();

}


void CJASDK_demoDlg::OnBnClickedZhuatu()
{
	// TODO: 在此添加控件通知处理程序代码
	char picpath[256] ={0};
	sprintf(picpath,"D:\\picSnapshot%d.bmp",i_num);
	BOOL ret = JASDK_CapturePicture(RealPlay_handle[0],picpath);
	i_num++;
	if(ret == TRUE){
		char messagechar[512] ={0};
		sprintf(messagechar,"抓图成功,保存在：%s",picpath);
		MessageBox(messagechar);
	}else {
		char errnochar[256];
		sprintf(errnochar,"抓图失败，错误号：%d",JASDK_GetLastError());
		MessageBox("抓图失败");

	}

}


void CJASDK_demoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	JASDK_Logout(userId[0]);
	JASDK_Logout(userId[1]);
	JASDK_Logout(userId[2]);
	JASDK_Logout(userId[3]);
	JASDK_Destroy();
	CDialogEx::OnCancel();
}
void CJASDK_demoDlg::setUserPassword(char* user,int userlen,char*pwd,int pwdlen){
	memset(username,0,sizeof(username));
	memset(password,0,sizeof(password));
	if(user && (userlen >0 && userlen< sizeof(username))){
		strncpy(username,user,userlen);
	}
	if(password &&(pwdlen >0 && pwdlen <sizeof(password))){
		strncpy(password,pwd,pwdlen);
	}
}

void CJASDK_demoDlg::sdknotify_ExceptionMessage(LONG lUserID,LONG lHandle,DWORD dwType,DWORD exNum,void *pUser){
	if(dwType){
		char errssdf[128]={0};
		int i =0,chn =0;;
		for(i =0;i<4;i++){
			if(userId[i] == lUserID){
				chn = i;
				break;
			}
		}
		switch(exNum){
		case JASDK_EXCEPTION_OFFLINE:		 //设备离线			
			sprintf(errssdf,"异常消息：第 %d个设备离线",chn);
			MessageBox(errssdf);
			break;
		case	 JASDK_EXCEPTION_TIMEOUT:		//连接超时
			sprintf(errssdf,"异常消息：第 %d个连接超时",chn);
			MessageBox(errssdf);
			break;
		case	 JASDK_EXCEPTION_FAILED:		 //连接失败
			sprintf(errssdf,"异常消息：第 %d个连接失败",chn);
			MessageBox(errssdf);
			break;
		case	 JASDK_EXCEPTION_CLOSE:		 //主动关闭
			sprintf(errssdf,"异常消息：第 %d个主动关闭",chn);
			MessageBox(errssdf);
			break;
		case  JASDK_EXCEPTION_CLOSEBYPEER:      //对端断开
			sprintf(errssdf,"异常消息：第 %d个对端断开",chn);
			MessageBox(errssdf);
			break;
		case JASDK_EXCEPTION_INIT_DEC:
			sprintf(errssdf,"异常消息：第 %d个解码器初始化失败",chn);
			MessageBox(errssdf);
			break;
		default:
			char errssdf[128]={0};
			sprintf(errssdf,"异常消息：%d",exNum);
			MessageBox(errssdf);break;
		};
	}

}

void CJASDK_demoDlg::OnBnClickedButton1()		//停止1  按钮
{
	JASDK_Logout(userId[0]);
	userId[0] = NULL;
	JASDK_Logout(userId[1]);
	userId[1] = NULL;
	JASDK_Logout(userId[2]);
	userId[2] = NULL;
	JASDK_Logout(userId[3]);
	userId[3] = NULL;

}


void CJASDK_demoDlg::OnBnClickedStopreal()
{
	JASDK_StopRealPlay(RealPlay_handle[ipc_num]);
	RealPlay_handle[ipc_num] =0; 
}

int istream =0;
void CJASDK_demoDlg::OnBnClickedRealplay()
{
	userId[ipc_num] = JASDK_Login("192.168.81.15",80,"admin",NULL,GMT_E8);
	STJASDK_CLIENTINFO clientInfo;
	memset(&clientInfo,0 ,sizeof(clientInfo));
	clientInfo.Channel = 0;
	clientInfo.Stream = (istream++)%2 ==0 ? 0:1;
	clientInfo.PlayWnd = GetDlgItem(E_STATIC_PIC_1)->GetSafeHwnd();
	RealPlay_handle[ipc_num] = JASDK_RealPlay(userId[ipc_num],&clientInfo);
	
	ipc_num =0;
/*	userId[ipc_num] = JASDK_Login_EseeId("100015721","admin",NULL,GMT_E8);
	
	if(0 == userId[ipc_num]){
		printf("error :%d \r\n",JASDK_GetLastError());
		int errnologin = (int)JASDK_GetLastError();
		switch(errnologin){
		case JASDK_NETWORK_FAIL_CONNECT:
			MessageBox("连接错误");
			break;
		case JASDK_PASSWORD_ERROR:
			MessageBox("用户名或密码错误");
			break;
		case JASDK_MEMORY_ERROR:
			MessageBox("内存错误");
			break;
		case JASDK_PARAMETER_ERROR:
			MessageBox("参数错误");
			break;
		}	
		return ;
	}
	STJASDK_CLIENTINFO clientInfo;
	memset(&clientInfo,0 ,sizeof(clientInfo));
	clientInfo.Channel = 0;
	clientInfo.Stream = 0;
	clientInfo.PlayWnd = GetDlgItem(E_STATIC_PIC_1)->GetSafeHwnd();
	RealPlay_handle[ipc_num] = JASDK_RealPlay(userId[ipc_num],&clientInfo);
	*/
	return ;
}


void CJASDK_demoDlg::OnBnClickedYuntai()
{
	// TODO: 在此添加控件通知处理程序代码
	ptz_dlg.setCJASDK_demoDlg(this,userId[0]);
	ptz_dlg.DoModal();
}

void  CJASDK_demoDlg::setRealPlayWND(int wndNUM){
	JASDK_setRealPlayWindow(userId[0],GetDlgItem(E_STATIC_PIC_1)->GetSafeHwnd());
}
