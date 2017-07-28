#pragma once
#ifndef __JASDK_H__
#define __JASDK_H__

#if (defined(WIN32)) //windows
#include "stdafx.h"

#define JASDK_API  extern "C"__declspec(dllimport)
typedef  unsigned __int64 UINT64;
#else   // not windows  === linux
typedef     unsigned int    DWORD;
typedef     unsigned short  WORD;
typedef     unsigned short  USHORT;
typedef     int             LONG;
typedef  	unsigned char	BYTE ;
#define     BOOL int
typedef     unsigned int   	UINT;
typedef 	void* 			LPVOID;
typedef 	void* 			HANDLE;
typedef     unsigned int*  LPDWORD; 
typedef  unsigned long long UINT64;
typedef		char			CHAR

#ifndef    TRUE
#define    TRUE	1
#endif
#ifndef    FALSE
#define	   FALSE 0
#endif
#ifndef    NULL
#define	   NULL 0
#endif


#define __stdcall 
#define CALLBACK  

#define JASDK_API extern "C"
typedef unsigned int   COLORKEY;
typedef unsigned int   COLORREF;

#ifndef __HWND_defined
#define __HWND_defined
	#if defined(__linux__)
		typedef unsigned int HWND;
	#else
		typedef void* HWND;
	#endif
#endif

#define JASDK_API extern "C"
typedef unsigned int   COLORKEY; 
typedef unsigned int   COLORREF; 

#ifndef __HDC_defined
#define __HDC_defined
    #if defined(__linux__)
    typedef struct __DC
    {
            void*   surface;        //SDL Surface
            HWND    hWnd;           // HDC window handle
    }DC;
    typedef DC* HDC;
    #else
    typedef void* HDC;
    #endif
#endif

typedef struct tagInitInfo
{
	int uWidth; 
	int uHeight; 
}INITINFO; 

#endif

#define SERIALNO_LEN 64
#define JASDK_NOERROR  0                //û�д���
#define JASDK_NETWORK_FAIL_CONNECT  1   //���ӷ�����ʧ��
#define JASDK_PASSWORD_ERROR  2         //�û��������������,��¼ʧ��
#define JASDK_MEMORY_ERROR 3			//�ڴ����ʧ�ܣ��ڴ治����
#define JASDK_PARAMETER_ERROR 4			//��������

#define JASDK_COMM_EXCEPTION                  0x11         //ͨ���쳣��Ϣ
#define JASDK_COMM_ALARM                      0x12         //ͨ�ñ�����Ϣ
#define JASDK_ALARM_WIRELESS                  0x13         //���߱�����Ϣ
#define JASDK_ALARM_UPS                       0x14         //UPS������Ϣ
#define JASDK_SEARCH_MSG                       0x15         //������Ϣ
#define JASDK_COMM_NET_MSG					0x16			//�����쳣��Ϣ

#define	 JASDK_EXCEPTION_OFFLINE		0x8801		 //�豸����
#define	 JASDK_EXCEPTION_TIMEOUT	   	0x8802		//���ӳ�ʱ
#define	 JASDK_EXCEPTION_FAILED			0x8803		 //����ʧ��
#define	 JASDK_EXCEPTION_CLOSE			0x8804		 //�����ر�,
#define  JASDK_EXCEPTION_CLOSEBYPEER	0x8805		//�Զ˶Ͽ�
#define	 JASDK_EXCEPTION_INIT_DEC		0x8806		 //�����ʼ������

#define  JASDK_KEYFRAMEDATA 1						//�ؼ�֡
#define  JASDK_VIDEOFRAMEDATA 2						//��ͨ��Ƶ֡
#define  JASDK_AUDIOFRAMEDATA 3						//��Ƶ֡

typedef enum{
	JASDK_PWD_TYPE_NONE,
	JASDK_PWD_TYPE_MD5,
}JASDK_PWD_TYPE;

typedef enum{
	DEVICE_TYPE_IPC = 1,
	DEVICE_TYPE_NVR ,
	DEVICE_TYPE_DVR,
	DEVICE_TYPE_IPHONE,
	DEVICE_TYPE_PC,
	DEVICE_TYPE_NET,
}JASDK_DEVICE_TYPE;

/**
 *  ��̨���ƶ���
 *  ��ʶ��Ч�������벻Ҫʹ��
 *  ����							����				param1					param2
 *  JASDK_PTZ_CMD_UP				������̨�����˶�	�˶��ٶȣ�ȡֵ0~7			��
 *  JASDK_PTZ_CMD_DOWN				������̨�����˶�	�˶��ٶȣ�ȡֵ0~7			��
 *  JASDK_PTZ_CMD_LEFT				������̨�����˶�	�˶��ٶȣ�ȡֵ0~7			��
 *  JASDK_PTZ_CMD_RIGHT,			������̨�����˶�	�˶��ٶȣ�ȡֵ0~7			��
 *  JASDK_PTZ_CMD_AUTOPAN,			�Զ�ˮƽ��ת		������ֹͣ�Զ���ȡֵ1����0	��
 *	JASDK_PTZ_CMD_IRIS_OPEN,		���ƹ�Ȧ��		��ͷ�ٶȣ�ȡֵ0~7			��
 *  JASDK_PTZ_CMD_IRIS_CLOSE,		���ƹ�Ȧ�ر�		��ͷ�ٶȣ�ȡֵ0~7			��
 *  JASDK_PTZ_CMD_ZOOM_IN,			����Զ��			��ͷ�ٶȣ�ȡֵ0~7			��
 *  JASDKv_PTZ_CMD_ZOOM_OUT,		��������			��ͷ�ٶȣ�ȡֵ0~7			��
 *  JASDK_PTZ_CMD_FOCUS_FAR,		�����䱶��		��ͷ�ٶȣ�ȡֵ0~7			��
 *  JASDK_PTZ_CMD_FOCUS_NEAR		�����䱶С		��ͷ�ٶȣ�ȡֵ0~7			��
 *  JASDK_PTZ_CMD_STOP,			ֹͣ��̨�˶�		��						��
 *  JASDK_PTZ_AUX1,				��������1		    ���غ�0					�򿪻�رգ�ȡֵ1��0
 *  JASDK_PTZ_AUX2,				��������2			���غ�1					�򿪻�رգ�ȡֵ1��0
 */
enum  JA_PTZ_CMD {
    JASDK_PTZ_CMD_NULL = -1,
    JASDK_PTZ_CMD_UP,
    JASDK_PTZ_CMD_DOWN,
    JASDK_PTZ_CMD_LEFT,
    JASDK_PTZ_CMD_RIGHT,
    JASDK_PTZ_CMD_LEFT_UP,			//��Ч����
    JASDK_PTZ_CMD_RIGHT_UP,		//��Ч����
    JASDK_PTZ_CMD_LEFT_DOWN,		//��Ч����
    JASDK_PTZ_CMD_RIGHT_DOWN,		//��Ч����
    JASDK_PTZ_CMD_AUTOPAN,
    JASDK_PTZ_CMD_IRIS_OPEN,
    JASDK_PTZ_CMD_IRIS_CLOSE,
    JASDK_PTZ_CMD_ZOOM_IN,
    JASDK_PTZ_CMD_ZOOM_OUT,
    JASDK_PTZ_CMD_FOCUS_FAR,
    JASDK_PTZ_CMD_FOCUS_NEAR,
    JASDK_PTZ_CMD_STOP,
    JASDK_PTZ_CMD_WIPPER_ON,		//��Ч����
    JASDK_PTZ_CMD_WIPPER_OFF,		//��Ч����
    JASDK_PTZ_CMD_LIGHT_ON,		//��Ч����
    JASDK_PTZ_CMD_LIGHT_OFF,		//��Ч����
    JASDK_PTZ_CMD_POWER_ON,		//��Ч����
    JASDK_PTZ_CMD_POWER_OFF,		//��Ч����
    JASDK_PTZ_CMD_GOTO_PRESET,		//��Ч����
    JASDK_PTZ_CMD_SET_PRESET,		//��Ч����
    JASDK_PTZ_CMD_CLEAR_PRESET,	//��Ч����
    JASDK_PTZ_CMD_TOUR,			//��Ч����
    JASDK_PTZ_CMD_AUX1,
    JASDK_PTZ_CMD_AUX2,
    JASDK_PTZ_CMD_CNT,
};

typedef struct JASDK_DEVICE_INFO{
	char device_name[64];
	char netmask[32];
	char gateway[32];
	char ether_lan[16];
	char device_mac[18];
	char esee_id[32];
	char device_scope[128];
	JASDK_PWD_TYPE password_type;		       // �û������������MD5 , ��
}STJASDK_DEVICE_INFO,*LPJASDK_DEVICE_INFO;

typedef struct
{
    BYTE sSerialNumber[SERIALNO_LEN];		//88888167,ID��
    BYTE AlarmInPortNum;					//����������
    BYTE AlarmOutPortNum;					//���������
    BYTE DiskNum;							//Ӳ�̸���
    BYTE Type;								//�豸����
    BYTE ChanNum;							//��Ƶ��
    BYTE AudioChanNum;						//��Ƶ��
	LPJASDK_DEVICE_INFO	ex_device_info;			//�豸��Ϣ,��չ�ģ�����Ϊ��
    BYTE Res[24];							//�����ֽ�
}STJASDK_LOGIN_DEVCEINFO, *LPJASDK_LOGIN_DEVCEINFO;

typedef struct
{
    LONG Channel;                    //ͨ����,��0��ʼ
    LONG Stream;					//������   0 ��������1 ��������2 IPC ��������
    LONG LinkMode;                   //���ӷ�ʽ
    HWND PlayWnd;                    //��Ƶ���Ŵ���
}STJASDK_CLIENTINFO, *LPJASDK_CLIENTINFO;

typedef enum {
	GMT_0 =0,
	GMT_E1,			//��1��
	GMT_E2,
	GMT_E3,
	GMT_E4,
	GMT_E5,
	GMT_E6,
	GMT_E7,
	GMT_E8,				//��8��������ʱ��
	GMT_E9,
	GMT_E10,
	GMT_E11,
	GMT_E12,
	GMT_W1,				//��1��
	GMT_W2,	
	GMT_W3,	
	GMT_W4,	
	GMT_W5,	
	GMT_W6,	
	GMT_W7,	
	GMT_W8,	
	GMT_W9,	
	GMT_W10,	
	GMT_W11,	
	GMT_W12,	
}JASDK_TIMEZONE;


typedef struct AVI_SAVE_INFO{
	char filename[128];
	int v_h;
	int v_w;
	int v_fps;
	char v_compressor[8];     //��x264��
	int a_channels;
	long a_rate;
	int a_bits;
	int a_format;
}STAVI_SAVE_INFO; 


//SDK��ʼ��
BOOL __stdcall JASDK_Init();
BOOL __stdcall JASDK_Destroy();

//SDKע��
/***************************************
*�û�ע���豸��
*
*
*Return Values ����ֵ NULL ʧ�ܣ�����ֵ��ʾ���ص��û�IDֵ,lUserID�����û�ID����Ψһ�ԣ��������豸�Ĳ�������Ҫͨ����IDʵ�֡�
****************************************/
LONG __stdcall JASDK_Login( char *sIP,WORD wPort, char *sUserName,char *sPassword,JASDK_TIMEZONE timeZone);
LONG __stdcall JASDK_Login_EseeId(char *eseeid , char *sUserName,char *sPassword,JASDK_TIMEZONE tz);
BOOL __stdcall JASDK_Logout(LONG lUserID);

//��ȡ�汾��
JASDK_API CHAR* __stdcall JASDK_GetSDKVersion();

//ȡ������
JASDK_API DWORD __stdcall JASDK_GetLastError();

typedef void (*fExceptionCallBack)(LONG lUserID,LONG lHandle,DWORD dwType,DWORD exNum,void *pUser);

//������Ϣ�ص�
JASDK_API BOOL __stdcall JASDK_SetSDKMessage(fExceptionCallBack cbExceptionCallBack,void *pUser);

//��ȡ���ͨ����
JASDK_API int __stdcall JASDK_getChannelCount(LONG lUserID);

//��ƵԤ��
/*
*Return Values ����ֵ�� -1��ʾʧ�ܣ�����ֵ��ΪJASDK_StopRealPlay�Ⱥ����ľ��������
*/
JASDK_API LONG __stdcall JASDK_RealPlay(LONG lUserID, LPJASDK_CLIENTINFO lpClientInfo);
JASDK_API BOOL __stdcall JASDK_StopRealPlay(LONG lRealHandle);
JASDK_API BOOL __stdcall JASDK_setRealPlayWindow(LONG lUserID, HWND PlayWnd);

//ʵʱ���ݻ�ȡ������ʱH264��ʽһ֡����
/*
Callback Function Parameters

	lRealHandle 
		��ǰ��Ԥ����� 
	dwDataType 
		�������� �궨�� �궨��ֵ ���� 
		JASDK_KEYFRAMEDATA 1 �ؼ�֡���� 
		JASDK_VIDEOFRAMEDATA 2 ��ͨ��Ƶ֡����
		JASDK_AUDIOFRAMEDATA 3 ��Ƶ֡���� 
	pBuffer 
		������ݵĻ�����ָ�� 
	dwBufSize 
		��������С 
	dwUser 
		�û����� 

Return Values
	TRUE��ʾ�ɹ���FALSE��ʾʧ�ܡ���ȡ���������JASDK_GetLastError

Remarks
	�˺���������ʼ��ֹͣ�û�����SDK��������ݣ����ص�����cbRealDataCallBack��Ϊ��NULLֵʱ����ʾ�ص��ʹ������ݣ���	��ΪNULLʱ��ʾֹͣ�ص��ʹ������ݡ�

*/
typedef void( *fRealDataCallBack)( LONG lRealHandle, DWORD dwDataType,BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser);

/*
ע��ص�����������ʵʱ�������ݡ�
lRealHandle 		[in] JASDK_RealPlay()�ķ���ֵ 
cbRealDataCallBack 	[in] �������ݻص����� 
dwUser				[in] �û����� 
*/
JASDK_API BOOL __stdcall JASDK_SetRealDataCallBack(LONG lRealHandle, fRealDataCallBack cbRealDataCallBack, DWORD dwUser);

/*
�������ݲ���ŵ�ָ�����ļ��С�H264��ʽ���ļ�
Parameters
	lRealHandle [in] JASDK_RealPlay()�ķ���ֵ 
	sFileName 	[in] �ļ�·��ָ�� ,С��256�ַ� 
Return Values
	TRUE��ʾ�ɹ���FALSE��ʾʧ�ܡ���ȡ���������JASDK_GetLastError

See Also
	JASDK_RealPlay  JASDK_StopSaveRealData

*/
JASDK_API BOOL __stdcall JASDK_SaveRealData(LONG lRealHandle,char *sFileName);

/*
ֹͣ���ݲ���
Parameters
	lRealHandle 	[in] JASDK_RealPlay()�ķ���ֵ 

Return Values		TRUE��ʾ�ɹ���FALSE��ʾʧ�ܡ���ȡ���������JASDK_GetLastError

See Also			JASDK_RealPlay  JASDK_SaveRealData

*/
JASDK_API BOOL __stdcall JASDK_StopSaveRealData(LONG lRealHandle);

/*
�������ݲ���ŵ�ָ�����ļ��С�H264��ʽ���ļ�
Parameters
	lRealHandle [in] JASDK_RealPlay()�ķ���ֵ 
	info 		[in] avi����·���� ����Ƶ��������Ƶ������ 
Return Values
	TRUE��ʾ�ɹ���FALSE��ʾʧ�ܡ���ȡ���������JASDK_GetLastError

See Also
	JASDK_RealPlay  JASDK_StopSaveRealData

*/
JASDK_API BOOL __stdcall JASDK_SaveRealData_AVI(LONG lRealHandle,STAVI_SAVE_INFO* info);

/*
ֹͣAVI���ݲ���
Parameters
	lRealHandle 	[in] JASDK_RealPlay()�ķ���ֵ 

Return Values		TRUE��ʾ�ɹ���FALSE��ʾʧ�ܡ���ȡ���������JASDK_GetLastError

See Also			JASDK_RealPlay  JASDK_SaveRealData

*/
JASDK_API BOOL __stdcall JASDK_StopSaveRealData_AVI(LONG lRealHandle);

/*
��֡���ݲ��񲢱����BMPλͼ��

Parameters
	lRealHandle		[in] JASDK_RealPlay()�ķ���ֵ 
	sPicFileName 	[in] ����BMPͼ����ļ�·������׺Ϊ.bmp���ļ�·���ĳ���С��256�ֽ� 

Return Values		TRUE��ʾ�ɹ���FALSE��ʾʧ�ܡ���ȡ���������JASDK_GetLastError

Remarks				�ýӿ�����ץȡ����ʱ�ĵ�ǰһ֡��BMPͼ�� 

See Also			JASDK_RealPlay

*/
BOOL JASDK_CapturePicture(LONG lRealHandle,char *sPicFileName);


/////////////////////////////////////BACKPLAY////////////////////////////

typedef struct
{
    DWORD dwYear;          //��
    DWORD dwMonth;         //��
    DWORD dwDay;           //��
    DWORD dwHour;          //Сʱ
    DWORD dwMinute;        //��
    DWORD dwSecond;        //��
}STJASDK_PLAYBACK_TIME, *LPJASDK_PLAYBACK_TIME;

typedef struct
{
	char sFileName[100];
	int nChannel;
	int type;
    STJASDK_PLAYBACK_TIME struStartTime;
	STJASDK_PLAYBACK_TIME struStopTime;
    DWORD dwFileSize;  
}STJASDK_FIND_DATA, *LPJASDK_FIND_DATA;

#define JASDK_PLAYBACK_FILE_SUCCESS    1000 
#define JASDK_PLAYBACK_FILE_NOFIND     1001
#define JASDK_PLAYBACK_ISFINDING       1002 
#define JASDK_PLAYBACK_NOMOREFILE      1003
#define JASDK_PLAYBACK_FILE_EXCEPTION  1004
#define	JASDK_PLAYBACK_PLAYSTART 1
#define	JASDK_PLAYBACK_PLAYPAUSE 2
#define	JASDK_PLAYBACK_PLAYRESTART 3

//¼���ļ�����

/*
�����ļ����͡�ʱ������豸¼���ļ���
Parameters
	lUserID			[in] JASDK_Login()�ķ���ֵ 
	lChannel 		[in] ͨ���� 
	dwFileType 		[in] Ҫ���ҵ��ļ����ͣ�0xff-ȫ����0-��ʱ¼��1-�ƶ���⣻2-����������3-�ֶ�¼��
	lpStartTime 	[in] �ļ��Ŀ�ʼʱ��,Ҫע��ʱ�������籱��ʱ����Ҫgmtʱ��+8
	lpStopTime 		[in] �ļ��Ľ���ʱ�� ֻ�ܸ���ʼʱ����һ���

Return Values
	NULL��ʾʧ�ܣ�����ֵ��ΪJASDK_PLAYBACK_FindClose�Ⱥ����Ĳ�������ȡ���������JASDK_GetLastError

Remarks
	�ýӿ�ָ����Ҫ���ҵ�¼���ļ������ͺͲ���ʱ�䷶Χ�����óɹ��󣬾Ϳ��Ե���JASDK_PLAYBACK_FindNextFile�ӿ�����ȡ�ļ���Ϣ�� 


*/
LONG __stdcall JASDK_PLAYBACK_FindFile(LONG lUserID,LONG lChannel,DWORD dwFileType,LPJASDK_PLAYBACK_TIME lpStartTime,LPJASDK_PLAYBACK_TIME  lpStopTime);

/*
�����ȡ���ҵ����ļ���Ϣ��
Parameters
	lFindHandle 		[in] �ļ����Ҿ����JASDK_FindFile()�ķ���ֵ 
	lpFindData			[out] �����ļ���Ϣ��ָ�� 

Return Values		JASDK_PLAYBACK_FILE_SUCCESS ��ʾ�ɹ�������ֵ��ʾ��ǰ�Ļ�ȡ״̬����Ϣ������±���ȡ���������JASDK_GetLastError

�궨��                   �궨��ֵ        ���� 
JASDK_PLAYBACK_FILE_SUCCESS    1000           ��ȡ�ļ���Ϣ�ɹ� 
JASDK_PLAYBACK_FILE_NOFIND     1001           δ���ҵ��ļ� 
JASDK_PLAYBACK_ISFINDING       1002           ���ڲ�����ȴ� 
JASDK_PLAYBACK_NOMOREFILE      1003           û�и�����ļ������ҽ��� 
JASDK_PLAYBACK_FILE_EXCEPTION  1004           �����ļ�ʱ�쳣 

Remarks
	�ڵ��øýӿڻ�ȡ�����ļ�֮ǰ�������ȵ���STJASDK_FindFile�õ���ǰ�Ĳ��Ҿ����

*/
LONG __stdcall JASDK_PLAYBACK_FindNextFile(LONG lFindHandle,LPJASDK_FIND_DATA lpFindData);

/*
�ر��ļ����ң��ͷ���Դ��

Parameters
	lFindHandle 	[in] �ļ����Ҿ��JASDK_FindFile�ķ���ֵ 

Return Values		TRUE��ʾ�ɹ���FALSE��ʾʧ�ܡ���ȡ���������JASDK_GetLastError

*/
BOOL __stdcall JASDK_PLAYBACK_FindClose(LONG lFindHandle);

////¼��ط�

/*
��ʱ��ط�¼���ļ���
Parameters
	lUserID 		[in] JASDK_Login()�ķ���ֵ 
	lChannel 		[in] ͨ���� 
	lpStartTime 	[in] �ļ��Ŀ�ʼʱ�� 
	lpStopTime 		[in] �ļ�����ʱ�� 
	hWnd			[in] �طŵĴ��ھ��������Ϊ�գ�SDK�����յ��������ݣ�����������ʾ 

Return Values		0��ʾʧ�ܣ�����ֵ��ΪJASDK_StopPlayBack�Ⱥ����Ĳ�������ȡ���������JASDK_GetLastError

Remarks
	�ýӿ�ָ���˵�ǰҪ���ŵ�¼���ļ������óɹ��󣬿��Ե���JASDK_PlayBackControl�ӿڿ��Ʋ��š�
     �ڵ��øýӿڳɹ��󣬿���ͨ���ӿ�JASDK_SetPlayDataCallBackע��ص�����������¼����������ݲ����д���
*/
LONG __stdcall JASDK_PlayBackByTime(LONG lUserID,LONG lChannel, LPJASDK_PLAYBACK_TIME lpStartTime, LPJASDK_PLAYBACK_TIME lpStopTime, HWND hWnd);

/*
����¼��طŵ�״̬��

Parameters
	lPlayHandle 		[in] ���ž����JASDK_PlayBackByName��JASDK_PlayBackByTime�ķ���ֵ 
	dwControlCode 		[in] ����¼��ط�״̬������±� �궨�� �궨��ֵ ���� 
							JASDK_PLAYBACK_PLAYSTART 1 ��ʼ���� 
							JASDK_PLAYBACK_PLAYPAUSE 2 ��ͣ���� 
							JASDK_PLAYBACK_PLAYRESTART 3 �ָ����� 
	dwInValue			[in] ���õĲ��� 
	lpOutValue			[out] ��ȡ�Ĳ���

Return Values			TRUE��ʾ�ɹ���FALSE��ʾʧ�ܡ���ȡ���������JASDK_GetLastError

Remarks
�ýӿ��еĵ����������Ƿ���Ҫ������ֵ����������й�
*/
BOOL __stdcall JASDK_PlayBackControl(LONG lPlayHandle,DWORD dwControlCode,DWORD dwInValue,DWORD *LPOutValue);

/*
ֹͣ�ط�¼���ļ���
Parameters
	lPlayHandle 		[in] �طž����JASDK_PlayBackByTime����JASDK_PlayBackByName�ķ���ֵ 

Return Values			TRUE��ʾ�ɹ���FALSE��ʾʧ�ܡ���ȡ���������JASDK_GetLastError
*/
BOOL __stdcall JASDK_StopPlayBack(LONG lPlayHandle);


//¼�����ݲ���, ����
/*
�ص���������JASDK_SetPlayDataCallBack��ע��
	lPlayHandle 
		��ǰ��¼�񲥷ž�� 
	dwDataType 
		�������� �궨�� �궨��ֵ ���� 
		JASDK_KEYFRAMEDATA 1 �ؼ�֡���� 
		JASDK_VIDEOFRAMEDATA 2 ��ͨ��Ƶ֡����
		JASDK_AUDIOFRAMEDATA 3 ��Ƶ֡���� 
	pBuffer 
		������ݵĻ�����ָ�� 
	dwBufSize 
		��������С 
	dwUser 
		�û����� 

*/
typedef void(*fPlayDataCallBack)(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser);

/*
ע��ص�����������¼�����ݡ�

Parameters
	lPlayHandle 			[in] ���ž����JASDK_PlayBackByTime�ķ���ֵ 
	fPlayDataCallBack 		[in] ¼�����ݻص����� 
	dwUser					[in] �û����� 

Return Values
	TRUE��ʾ�ɹ���FALSE��ʾʧ�ܡ���ȡ���������JASDK_GetLastError

Remarks
	�˺���������ʼ��ֹͣ�û�����SDK��������ݣ����ص�����cbPlayDataCallBack��Ϊ��NULLֵʱ����ʾ�ص��ʹ������ݣ�����ΪNULLʱ��ʾֹͣ�ص��ʹ������ݡ�

*/
BOOL __stdcall JASDK_PlayBack_SetPlayDataCallBack(LONG lPlayHandle,fPlayDataCallBack callback,DWORD dwUser);

/*
����ʱ�䱣���ļ���
Parameters
	lUserID 			[in] JASDK_Login�ķ���ֵ 
	lChannel 			[in] ͨ���� 
	lpStartTime 		[in] ��ʼʱ�� 
	lpStopTime 			[in] ����ʱ�� 
	sSavedFileName 		[in] ���غ󱣴浽PC�����ļ�·�� 


Return Values
	0��ʾʧ�ܣ�����ֵ��ΪJASDK_PlayBack_StopGetFile�Ⱥ����Ĳ�������ȡ���������JASDK_GetLastError
Remarks
	Ԥ����ʱ�򲻿��Ա��棬�����ʱ�򲻿���Ԥ������Ҫ����ͻص��Լ������ļ���


*/
LONG __stdcall JASDK_PlayBack_GetFileByTime(int lUserID, int lChannel, LPJASDK_PLAYBACK_TIME lpStartTime, LPJASDK_PLAYBACK_TIME lpStopTime, char *sSavedFileName);

/*
ֹͣ����¼�����ݡ�

Parameters
	lPlayHandle 		[in] ���ž����JASDK_GetFileByTime �� JASDK_GetFileByName�ķ���ֵ 

Return Values
	TRUE��ʾ�ɹ���FALSE��ʾʧ�ܡ���ȡ���������JASDK _GetLastError
*/
BOOL __stdcall JASDK_PlayBack_StopGetFile(int lFileHandle);


//¼��ط�ץͼ
/*

¼��ط�ʱץͼ�����������ļ��С�

Parameters
	lPlayHandle 	[in] ���ž����JASDK_PlayBackByTime�ķ���ֵ 
	sFileName 		[in] ����ͼƬ���ݵ��ļ�·�� 

Return Values		TRUE��ʾ�ɹ���FALSE��ʾʧ�ܡ���ȡ���������JASDK_GetLastError

See Also
	JASDK_PlayBackByTime  �� JASDK_PlayBackByName

*/
BOOL __stdcall JASDK_PlayBackCaptureFile(LONG lPlayHandle,char *sFileName);

/**
 *  P2P��̨����
 *
 *  @param p2p_handle �Ѿ����ӵ�P2P���,JASDK_Login�ķ���ֵ
 *  @param nChannel   ��̨����ͨ����
 *  @param act        ��̨��������
 *  @param bStart     1,��̨������ʼ;0,��̨����ֹͣ
 *  @param param1     ��̨��������1
 *  @param param2     ��̨��������2
 *
 *  @return TRUE:		�����ɹ�
 *			FALSE��		������ʱ
 */

int __stdcall JASDK_PTZ_CTRL(LONG lUserID, int nChannel,int act, int bStart, int param1,int param2);

#endif
