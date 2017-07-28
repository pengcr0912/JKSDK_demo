
// JASDK_demoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JASDK_demo.h"
#include "JASDK_demoDlg.h"
#include "afxdialogex.h"
#include "JASDK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// CJASDK_demoDlg �Ի���
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


// CJASDK_demoDlg ��Ϣ�������

BOOL CJASDK_demoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
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
	GetDlgItem(IDC_CZSM)->SetWindowText("���������豸���ȵ���������豸����ť�������������ڣ��������������ť���������豸�б�ѡ����Ҫ��ʾ���豸��˫���Ϳ����ˡ�\
Ŀǰֻ�У��������豸�������طš�����¼�񡱣���ץͼ������ʹ��\
��¼�񡱺͡�ץͼ����ťֻ������Ƶ����ʱ����Ч\
�طŴ���,ֻ��������ʼ�ĵ����¼����Ƶ��������Ƶʱ���������أ����ز��ܲ��š��طŲ���ʱ����ץͼ��");
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CJASDK_demoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	
		//�����������������
		memset(username,0,sizeof(username));
		memset(password,0,sizeof(password));
		userPwdDlg.setDemoDlg((void*)this);
		userPwdDlg.DoModal();
		//����Ѿ�������ƵԤ������ɾ��
		int i;
//		for( i=0; i < DISPLAY_NUM; i++){
//			if(NULL != userId[i]){
//				JASDK_StopRealPlay(RealPlay_handle[i]);
//				JASDK_Logout(userId[i]);
//				userId[i] = NULL;
//				RealPlay_handle[i] = NULL;
//			}
//		}
		
		//��ƵԤ��,IPC
		if((strcmp(info->device_model,"IPCAM") ==0) || (strcmp(info->device_model,"IPC") ==0)){
			//ע�ᣬ��֤����
			userId[ipc_num] = JASDK_Login(info->ip,atoi(info->port), strlen(username)>0?username:NULL,strlen(password)>0?password:NULL,GMT_E8);
//			userId[ipc_num] = JASDK_Login_EseeId("545413455","admin",NULL,GMT_E8);
			if(0 == userId[ipc_num]){
				printf("error :%d \r\n",JASDK_GetLastError());
				int errnologin = (int)JASDK_GetLastError();
				switch(errnologin){
				case JASDK_NETWORK_FAIL_CONNECT:
					MessageBox("���Ӵ���");
					break;
				case JASDK_PASSWORD_ERROR:
					MessageBox("�û������������");
					break;
				case JASDK_MEMORY_ERROR:
					MessageBox("�ڴ����");
					break;
				case JASDK_PARAMETER_ERROR:
					MessageBox("��������");
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
						MessageBox("���Ӵ���");
						break;
					case JASDK_PASSWORD_ERROR:
						MessageBox("�û������������");
						break;
					case JASDK_MEMORY_ERROR:
						MessageBox("�ڴ����");
						break;
					case JASDK_PARAMETER_ERROR:
						MessageBox("��������");
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
			MessageBox("���Ӵ���");
			break;
		case JASDK_PASSWORD_ERROR:
			MessageBox("�û������������");
			break;
		case JASDK_MEMORY_ERROR:
			MessageBox("�ڴ����");
			break;
		case JASDK_PARAMETER_ERROR:
			MessageBox("��������");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void CJASDK_demoDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	//���ݻص�
/*
	if(b_savefile1 == false){
		char lpszStringBuf[64]={0};
		_snprintf(lpszStringBuf,64,"d:\\realPlayCallback%d.h264",i_num);
		saveFile1(lpszStringBuf,strlen(lpszStringBuf),1);
		char bufpuzhuo[128]={0};
		_snprintf(bufpuzhuo,128,"���ݲ�׽�������ļ���D��:%s",lpszStringBuf);
		MessageBox(bufpuzhuo);
	}else{
		char lpszStringBuf[64]={0};
		saveFile1(lpszStringBuf,strlen(lpszStringBuf),0);
		MessageBox("����ȡ����׽");
	}
	//���ݱ����ļ�
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
	
	//���ݱ����ļ�
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
	//����ֻΪ JASDK_SetRealDataCallBack��fRealDataCallBack ����ʾ����ֱ�ӱ��浽�ļ������ˡ�
	if(flag ==0){ //
		if(fp){
			fclose(fp);
		}
		b_savefile1 = false;
		JASDK_SetRealDataCallBack(RealPlay_handle[0],(fRealDataCallBack)NULL, (DWORD)NULL);
	}else {
		if((strlen(path1) >0 && (strlen(path1)<256) )&& (length >0)){
			int ret = JASDK_SetRealDataCallBack(RealPlay_handle[0],(fRealDataCallBack)demo_RealDataCallBack, (DWORD)this);
			if(ret == 0){ //������
				b_savefile1 = false;
				MessageBox("�ص����ó���");
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
				sprintf(shibai,"���ļ�ʧ��:%s",path1);
				MessageBox(shibai);
			}
		}
	}

}
void CJASDK_demoDlg::saveFile2(char* path2,int length,int flag){
	//����ֻΪ  ��ʾ
	if(flag ==0 ){
		b_savefile2 = false;
		memset(filepath2,0,sizeof(filepath2));
		JASDK_StopSaveRealData(RealPlay_handle[0]);
		MessageBox("�ر�ʵʱ¼��");
		return;
	}

	//�����ļ�
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
			MessageBox("ʵʱ¼������ʧ��");
		}
		
	}

	if(b_savefile2){
		char luxiangwenjian[128]={0};
		sprintf(luxiangwenjian,"ʵʱ¼��¼���ļ���%s",path2);
		MessageBox(luxiangwenjian);
//		b_luxiang_l.SetWindowTextA("����¼��");
	}else{
		MessageBox("�ر�ʵʱ¼��");
//		b_luxiang_l.SetWindowTextA("¼��");
	}

}
#define WAVE_FORMAT_PCM                 (0x0001)
#define WAVE_FORMAT_ALAW                (0x0006)
void CJASDK_demoDlg::saveFile_avi(char* avipath,int length,int flag){
	if(flag ==0 ){
		b_savefile_avi = false;
		memset(filepath_avi,0,sizeof(filepath_avi));
		JASDK_StopSaveRealData_AVI(RealPlay_handle[0]);
		MessageBox("�ر�ʵʱ¼��");
		return;
	}

	//�����ļ�
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
			MessageBox("ʵʱ¼������ʧ��");
		}

	}

	if(b_savefile_avi){
		char luxiangwenjian[128]={0};
		sprintf(luxiangwenjian,"ʵʱ¼��¼���ļ���%s",filepath_avi);
		MessageBox(luxiangwenjian);
		//		b_luxiang_l.SetWindowTextA("����¼��");
	}else{
		MessageBox("�ر�ʵʱ¼��");
		//		b_luxiang_l.SetWindowTextA("¼��");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	JASDK_StopRealPlay(RealPlay_handle[0]);
//	RealPlay_handle[0] = NULL;
	playBackDlg.setCJASDK_demoDlg(this,userId[0]);
	playBackDlg.DoModal();

}


void CJASDK_demoDlg::OnBnClickedZhuatu()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char picpath[256] ={0};
	sprintf(picpath,"D:\\picSnapshot%d.bmp",i_num);
	BOOL ret = JASDK_CapturePicture(RealPlay_handle[0],picpath);
	i_num++;
	if(ret == TRUE){
		char messagechar[512] ={0};
		sprintf(messagechar,"ץͼ�ɹ�,�����ڣ�%s",picpath);
		MessageBox(messagechar);
	}else {
		char errnochar[256];
		sprintf(errnochar,"ץͼʧ�ܣ�����ţ�%d",JASDK_GetLastError());
		MessageBox("ץͼʧ��");

	}

}


void CJASDK_demoDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		case JASDK_EXCEPTION_OFFLINE:		 //�豸����			
			sprintf(errssdf,"�쳣��Ϣ���� %d���豸����",chn);
			MessageBox(errssdf);
			break;
		case	 JASDK_EXCEPTION_TIMEOUT:		//���ӳ�ʱ
			sprintf(errssdf,"�쳣��Ϣ���� %d�����ӳ�ʱ",chn);
			MessageBox(errssdf);
			break;
		case	 JASDK_EXCEPTION_FAILED:		 //����ʧ��
			sprintf(errssdf,"�쳣��Ϣ���� %d������ʧ��",chn);
			MessageBox(errssdf);
			break;
		case	 JASDK_EXCEPTION_CLOSE:		 //�����ر�
			sprintf(errssdf,"�쳣��Ϣ���� %d�������ر�",chn);
			MessageBox(errssdf);
			break;
		case  JASDK_EXCEPTION_CLOSEBYPEER:      //�Զ˶Ͽ�
			sprintf(errssdf,"�쳣��Ϣ���� %d���Զ˶Ͽ�",chn);
			MessageBox(errssdf);
			break;
		case JASDK_EXCEPTION_INIT_DEC:
			sprintf(errssdf,"�쳣��Ϣ���� %d����������ʼ��ʧ��",chn);
			MessageBox(errssdf);
			break;
		default:
			char errssdf[128]={0};
			sprintf(errssdf,"�쳣��Ϣ��%d",exNum);
			MessageBox(errssdf);break;
		};
	}

}

void CJASDK_demoDlg::OnBnClickedButton1()		//ֹͣ1  ��ť
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
			MessageBox("���Ӵ���");
			break;
		case JASDK_PASSWORD_ERROR:
			MessageBox("�û������������");
			break;
		case JASDK_MEMORY_ERROR:
			MessageBox("�ڴ����");
			break;
		case JASDK_PARAMETER_ERROR:
			MessageBox("��������");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ptz_dlg.setCJASDK_demoDlg(this,userId[0]);
	ptz_dlg.DoModal();
}

void  CJASDK_demoDlg::setRealPlayWND(int wndNUM){
	JASDK_setRealPlayWindow(userId[0],GetDlgItem(E_STATIC_PIC_1)->GetSafeHwnd());
}
