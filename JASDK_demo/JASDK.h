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
#define JASDK_NOERROR  0                //没有错误
#define JASDK_NETWORK_FAIL_CONNECT  1   //连接服务器失败
#define JASDK_PASSWORD_ERROR  2         //用户名或者密码错误,登录失败
#define JASDK_MEMORY_ERROR 3			//内存分配失败，内存不够了
#define JASDK_PARAMETER_ERROR 4			//参数错误

#define JASDK_COMM_EXCEPTION                  0x11         //通用异常消息
#define JASDK_COMM_ALARM                      0x12         //通用报警消息
#define JASDK_ALARM_WIRELESS                  0x13         //无线报警消息
#define JASDK_ALARM_UPS                       0x14         //UPS报警消息
#define JASDK_SEARCH_MSG                       0x15         //搜索消息
#define JASDK_COMM_NET_MSG					0x16			//网络异常消息

#define	 JASDK_EXCEPTION_OFFLINE		0x8801		 //设备离线
#define	 JASDK_EXCEPTION_TIMEOUT	   	0x8802		//连接超时
#define	 JASDK_EXCEPTION_FAILED			0x8803		 //连接失败
#define	 JASDK_EXCEPTION_CLOSE			0x8804		 //主动关闭,
#define  JASDK_EXCEPTION_CLOSEBYPEER	0x8805		//对端断开
#define	 JASDK_EXCEPTION_INIT_DEC		0x8806		 //解码初始化错误

#define  JASDK_KEYFRAMEDATA 1						//关键帧
#define  JASDK_VIDEOFRAMEDATA 2						//普通视频帧
#define  JASDK_AUDIOFRAMEDATA 3						//音频帧

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
 *  云台控制动作
 *  标识无效的命令请不要使用
 *  命令							描述				param1					param2
 *  JASDK_PTZ_CMD_UP				控制云台向上运动	运动速度，取值0~7			无
 *  JASDK_PTZ_CMD_DOWN				控制云台向下运动	运动速度，取值0~7			无
 *  JASDK_PTZ_CMD_LEFT				控制云台向左运动	运动速度，取值0~7			无
 *  JASDK_PTZ_CMD_RIGHT,			控制云台向右运动	运动速度，取值0~7			无
 *  JASDK_PTZ_CMD_AUTOPAN,			自动水平旋转		开启或停止自动，取值1或者0	无
 *	JASDK_PTZ_CMD_IRIS_OPEN,		控制光圈打开		镜头速度，取值0~7			无
 *  JASDK_PTZ_CMD_IRIS_CLOSE,		控制光圈关闭		镜头速度，取值0~7			无
 *  JASDK_PTZ_CMD_ZOOM_IN,			调整远焦			镜头速度，取值0~7			无
 *  JASDKv_PTZ_CMD_ZOOM_OUT,		调整近焦			镜头速度，取值0~7			无
 *  JASDK_PTZ_CMD_FOCUS_FAR,		调整变倍大		镜头速度，取值0~7			无
 *  JASDK_PTZ_CMD_FOCUS_NEAR		调整变倍小		镜头速度，取值0~7			无
 *  JASDK_PTZ_CMD_STOP,			停止云台运动		无						无
 *  JASDK_PTZ_AUX1,				辅助开关1		    开关号0					打开或关闭，取值1或0
 *  JASDK_PTZ_AUX2,				辅助开关2			开关号1					打开或关闭，取值1或0
 */
enum  JA_PTZ_CMD {
    JASDK_PTZ_CMD_NULL = -1,
    JASDK_PTZ_CMD_UP,
    JASDK_PTZ_CMD_DOWN,
    JASDK_PTZ_CMD_LEFT,
    JASDK_PTZ_CMD_RIGHT,
    JASDK_PTZ_CMD_LEFT_UP,			//无效命令
    JASDK_PTZ_CMD_RIGHT_UP,		//无效命令
    JASDK_PTZ_CMD_LEFT_DOWN,		//无效命令
    JASDK_PTZ_CMD_RIGHT_DOWN,		//无效命令
    JASDK_PTZ_CMD_AUTOPAN,
    JASDK_PTZ_CMD_IRIS_OPEN,
    JASDK_PTZ_CMD_IRIS_CLOSE,
    JASDK_PTZ_CMD_ZOOM_IN,
    JASDK_PTZ_CMD_ZOOM_OUT,
    JASDK_PTZ_CMD_FOCUS_FAR,
    JASDK_PTZ_CMD_FOCUS_NEAR,
    JASDK_PTZ_CMD_STOP,
    JASDK_PTZ_CMD_WIPPER_ON,		//无效命令
    JASDK_PTZ_CMD_WIPPER_OFF,		//无效命令
    JASDK_PTZ_CMD_LIGHT_ON,		//无效命令
    JASDK_PTZ_CMD_LIGHT_OFF,		//无效命令
    JASDK_PTZ_CMD_POWER_ON,		//无效命令
    JASDK_PTZ_CMD_POWER_OFF,		//无效命令
    JASDK_PTZ_CMD_GOTO_PRESET,		//无效命令
    JASDK_PTZ_CMD_SET_PRESET,		//无效命令
    JASDK_PTZ_CMD_CLEAR_PRESET,	//无效命令
    JASDK_PTZ_CMD_TOUR,			//无效命令
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
	JASDK_PWD_TYPE password_type;		       // 用户密码加密类型MD5 , 空
}STJASDK_DEVICE_INFO,*LPJASDK_DEVICE_INFO;

typedef struct
{
    BYTE sSerialNumber[SERIALNO_LEN];		//88888167,ID号
    BYTE AlarmInPortNum;					//报警输入数
    BYTE AlarmOutPortNum;					//报警输出数
    BYTE DiskNum;							//硬盘个数
    BYTE Type;								//设备类型
    BYTE ChanNum;							//视频数
    BYTE AudioChanNum;						//音频数
	LPJASDK_DEVICE_INFO	ex_device_info;			//设备信息,扩展的，可以为空
    BYTE Res[24];							//保留字节
}STJASDK_LOGIN_DEVCEINFO, *LPJASDK_LOGIN_DEVCEINFO;

typedef struct
{
    LONG Channel;                    //通道号,从0开始
    LONG Stream;					//码流号   0 主码流，1 次码流，2 IPC 第三码流
    LONG LinkMode;                   //连接方式
    HWND PlayWnd;                    //视频播放窗口
}STJASDK_CLIENTINFO, *LPJASDK_CLIENTINFO;

typedef enum {
	GMT_0 =0,
	GMT_E1,			//东1区
	GMT_E2,
	GMT_E3,
	GMT_E4,
	GMT_E5,
	GMT_E6,
	GMT_E7,
	GMT_E8,				//东8区，北京时间
	GMT_E9,
	GMT_E10,
	GMT_E11,
	GMT_E12,
	GMT_W1,				//西1区
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
	char v_compressor[8];     //“x264”
	int a_channels;
	long a_rate;
	int a_bits;
	int a_format;
}STAVI_SAVE_INFO; 


//SDK初始化
BOOL __stdcall JASDK_Init();
BOOL __stdcall JASDK_Destroy();

//SDK注册
/***************************************
*用户注册设备。
*
*
*Return Values 返回值 NULL 失败，其他值表示返回的用户ID值,lUserID。该用户ID具有唯一性，后续对设备的操作都需要通过此ID实现。
****************************************/
LONG __stdcall JASDK_Login( char *sIP,WORD wPort, char *sUserName,char *sPassword,JASDK_TIMEZONE timeZone);
LONG __stdcall JASDK_Login_EseeId(char *eseeid , char *sUserName,char *sPassword,JASDK_TIMEZONE tz);
BOOL __stdcall JASDK_Logout(LONG lUserID);

//获取版本号
JASDK_API CHAR* __stdcall JASDK_GetSDKVersion();

//取错误码
JASDK_API DWORD __stdcall JASDK_GetLastError();

typedef void (*fExceptionCallBack)(LONG lUserID,LONG lHandle,DWORD dwType,DWORD exNum,void *pUser);

//设置消息回调
JASDK_API BOOL __stdcall JASDK_SetSDKMessage(fExceptionCallBack cbExceptionCallBack,void *pUser);

//获取最大通道数
JASDK_API int __stdcall JASDK_getChannelCount(LONG lUserID);

//视频预览
/*
*Return Values 返回值： -1表示失败，其他值作为JASDK_StopRealPlay等函数的句柄参数。
*/
JASDK_API LONG __stdcall JASDK_RealPlay(LONG lUserID, LPJASDK_CLIENTINFO lpClientInfo);
JASDK_API BOOL __stdcall JASDK_StopRealPlay(LONG lRealHandle);
JASDK_API BOOL __stdcall JASDK_setRealPlayWindow(LONG lUserID, HWND PlayWnd);

//实时数据获取，数据时H264格式一帧数据
/*
Callback Function Parameters

	lRealHandle 
		当前的预览句柄 
	dwDataType 
		数据类型 宏定义 宏定义值 含义 
		JASDK_KEYFRAMEDATA 1 关键帧数据 
		JASDK_VIDEOFRAMEDATA 2 普通视频帧数据
		JASDK_AUDIOFRAMEDATA 3 音频帧数据 
	pBuffer 
		存放数据的缓冲区指针 
	dwBufSize 
		缓冲区大小 
	dwUser 
		用户数据 

Return Values
	TRUE表示成功，FALSE表示失败。获取错误码调用JASDK_GetLastError

Remarks
	此函数包括开始和停止用户处理SDK捕获的数据，当回调函数cbRealDataCallBack设为非NULL值时，表示回调和处理数据；当	设为NULL时表示停止回调和处理数据。

*/
typedef void( *fRealDataCallBack)( LONG lRealHandle, DWORD dwDataType,BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser);

/*
注册回调函数，捕获实时码流数据。
lRealHandle 		[in] JASDK_RealPlay()的返回值 
cbRealDataCallBack 	[in] 码流数据回调函数 
dwUser				[in] 用户数据 
*/
JASDK_API BOOL __stdcall JASDK_SetRealDataCallBack(LONG lRealHandle, fRealDataCallBack cbRealDataCallBack, DWORD dwUser);

/*
捕获数据并存放到指定的文件中。H264格式的文件
Parameters
	lRealHandle [in] JASDK_RealPlay()的返回值 
	sFileName 	[in] 文件路径指针 ,小于256字符 
Return Values
	TRUE表示成功，FALSE表示失败。获取错误码调用JASDK_GetLastError

See Also
	JASDK_RealPlay  JASDK_StopSaveRealData

*/
JASDK_API BOOL __stdcall JASDK_SaveRealData(LONG lRealHandle,char *sFileName);

/*
停止数据捕获。
Parameters
	lRealHandle 	[in] JASDK_RealPlay()的返回值 

Return Values		TRUE表示成功，FALSE表示失败。获取错误码调用JASDK_GetLastError

See Also			JASDK_RealPlay  JASDK_SaveRealData

*/
JASDK_API BOOL __stdcall JASDK_StopSaveRealData(LONG lRealHandle);

/*
捕获数据并存放到指定的文件中。H264格式的文件
Parameters
	lRealHandle [in] JASDK_RealPlay()的返回值 
	info 		[in] avi保存路径名 ，视频参数，音频参数。 
Return Values
	TRUE表示成功，FALSE表示失败。获取错误码调用JASDK_GetLastError

See Also
	JASDK_RealPlay  JASDK_StopSaveRealData

*/
JASDK_API BOOL __stdcall JASDK_SaveRealData_AVI(LONG lRealHandle,STAVI_SAVE_INFO* info);

/*
停止AVI数据捕获。
Parameters
	lRealHandle 	[in] JASDK_RealPlay()的返回值 

Return Values		TRUE表示成功，FALSE表示失败。获取错误码调用JASDK_GetLastError

See Also			JASDK_RealPlay  JASDK_SaveRealData

*/
JASDK_API BOOL __stdcall JASDK_StopSaveRealData_AVI(LONG lRealHandle);

/*
单帧数据捕获并保存成BMP位图。

Parameters
	lRealHandle		[in] JASDK_RealPlay()的返回值 
	sPicFileName 	[in] 保存BMP图象的文件路径，后缀为.bmp，文件路径的长度小于256字节 

Return Values		TRUE表示成功，FALSE表示失败。获取错误码调用JASDK_GetLastError

Remarks				该接口用于抓取解码时的当前一帧的BMP图像。 

See Also			JASDK_RealPlay

*/
BOOL JASDK_CapturePicture(LONG lRealHandle,char *sPicFileName);


/////////////////////////////////////BACKPLAY////////////////////////////

typedef struct
{
    DWORD dwYear;          //年
    DWORD dwMonth;         //月
    DWORD dwDay;           //日
    DWORD dwHour;          //小时
    DWORD dwMinute;        //分
    DWORD dwSecond;        //秒
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

//录像文件查找

/*
根据文件类型、时间查找设备录像文件。
Parameters
	lUserID			[in] JASDK_Login()的返回值 
	lChannel 		[in] 通道号 
	dwFileType 		[in] 要查找的文件类型：0xff-全部；0-定时录像；1-移动侦测；2-报警触发；3-手动录像；
	lpStartTime 	[in] 文件的开始时间,要注意时区，比如北京时间需要gmt时间+8
	lpStopTime 		[in] 文件的结束时间 只能跟开始时间是一天的

Return Values
	NULL表示失败，其他值作为JASDK_PLAYBACK_FindClose等函数的参数。获取错误码调用JASDK_GetLastError

Remarks
	该接口指定了要查找的录像文件的类型和查找时间范围，调用成功后，就可以调用JASDK_PLAYBACK_FindNextFile接口来获取文件信息。 


*/
LONG __stdcall JASDK_PLAYBACK_FindFile(LONG lUserID,LONG lChannel,DWORD dwFileType,LPJASDK_PLAYBACK_TIME lpStartTime,LPJASDK_PLAYBACK_TIME  lpStopTime);

/*
逐个获取查找到的文件信息。
Parameters
	lFindHandle 		[in] 文件查找句柄，JASDK_FindFile()的返回值 
	lpFindData			[out] 保存文件信息的指针 

Return Values		JASDK_PLAYBACK_FILE_SUCCESS 标示成功，其他值表示当前的获取状态等信息，详见下表。获取错误码调用JASDK_GetLastError

宏定义                   宏定义值        含义 
JASDK_PLAYBACK_FILE_SUCCESS    1000           获取文件信息成功 
JASDK_PLAYBACK_FILE_NOFIND     1001           未查找到文件 
JASDK_PLAYBACK_ISFINDING       1002           正在查找请等待 
JASDK_PLAYBACK_NOMOREFILE      1003           没有更多的文件，查找结束 
JASDK_PLAYBACK_FILE_EXCEPTION  1004           查找文件时异常 

Remarks
	在调用该接口获取查找文件之前，必须先调用STJASDK_FindFile得到当前的查找句柄。

*/
LONG __stdcall JASDK_PLAYBACK_FindNextFile(LONG lFindHandle,LPJASDK_FIND_DATA lpFindData);

/*
关闭文件查找，释放资源。

Parameters
	lFindHandle 	[in] 文件查找句柄JASDK_FindFile的返回值 

Return Values		TRUE表示成功，FALSE表示失败。获取错误码调用JASDK_GetLastError

*/
BOOL __stdcall JASDK_PLAYBACK_FindClose(LONG lFindHandle);

////录像回放

/*
按时间回放录像文件。
Parameters
	lUserID 		[in] JASDK_Login()的返回值 
	lChannel 		[in] 通道号 
	lpStartTime 	[in] 文件的开始时间 
	lpStopTime 		[in] 文件结束时间 
	hWnd			[in] 回放的窗口句柄，若置为空，SDK仍能收到码流数据，但不解码显示 

Return Values		0表示失败，其他值作为JASDK_StopPlayBack等函数的参数。获取错误码调用JASDK_GetLastError

Remarks
	该接口指定了当前要播放的录像文件，调用成功后，可以调用JASDK_PlayBackControl接口控制播放。
     在调用该接口成功后，可以通过接口JASDK_SetPlayDataCallBack注册回调函数，捕获录像的码流数据并自行处理。
*/
LONG __stdcall JASDK_PlayBackByTime(LONG lUserID,LONG lChannel, LPJASDK_PLAYBACK_TIME lpStartTime, LPJASDK_PLAYBACK_TIME lpStopTime, HWND hWnd);

/*
控制录像回放的状态。

Parameters
	lPlayHandle 		[in] 播放句柄，JASDK_PlayBackByName或JASDK_PlayBackByTime的返回值 
	dwControlCode 		[in] 控制录像回放状态命令，见下表 宏定义 宏定义值 含义 
							JASDK_PLAYBACK_PLAYSTART 1 开始播放 
							JASDK_PLAYBACK_PLAYPAUSE 2 暂停播放 
							JASDK_PLAYBACK_PLAYRESTART 3 恢复播放 
	dwInValue			[in] 设置的参数 
	lpOutValue			[out] 获取的参数

Return Values			TRUE表示成功，FALSE表示失败。获取错误码调用JASDK_GetLastError

Remarks
该接口中的第三个参数是否需要输入数值与控制命令有关
*/
BOOL __stdcall JASDK_PlayBackControl(LONG lPlayHandle,DWORD dwControlCode,DWORD dwInValue,DWORD *LPOutValue);

/*
停止回放录像文件。
Parameters
	lPlayHandle 		[in] 回放句柄，JASDK_PlayBackByTime或者JASDK_PlayBackByName的返回值 

Return Values			TRUE表示成功，FALSE表示失败。获取错误码调用JASDK_GetLastError
*/
BOOL __stdcall JASDK_StopPlayBack(LONG lPlayHandle);


//录像数据捕获, 下载
/*
回调函数，在JASDK_SetPlayDataCallBack中注册
	lPlayHandle 
		当前的录像播放句柄 
	dwDataType 
		数据类型 宏定义 宏定义值 含义 
		JASDK_KEYFRAMEDATA 1 关键帧数据 
		JASDK_VIDEOFRAMEDATA 2 普通视频帧数据
		JASDK_AUDIOFRAMEDATA 3 音频帧数据 
	pBuffer 
		存放数据的缓冲区指针 
	dwBufSize 
		缓冲区大小 
	dwUser 
		用户数据 

*/
typedef void(*fPlayDataCallBack)(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser);

/*
注册回调函数，捕获录像数据。

Parameters
	lPlayHandle 			[in] 播放句柄，JASDK_PlayBackByTime的返回值 
	fPlayDataCallBack 		[in] 录像数据回调函数 
	dwUser					[in] 用户数据 

Return Values
	TRUE表示成功，FALSE表示失败。获取错误码调用JASDK_GetLastError

Remarks
	此函数包括开始和停止用户处理SDK捕获的数据，当回调函数cbPlayDataCallBack设为非NULL值时，表示回调和处理数据；当设为NULL时表示停止回调和处理数据。

*/
BOOL __stdcall JASDK_PlayBack_SetPlayDataCallBack(LONG lPlayHandle,fPlayDataCallBack callback,DWORD dwUser);

/*
根据时间保存文件。
Parameters
	lUserID 			[in] JASDK_Login的返回值 
	lChannel 			[in] 通道号 
	lpStartTime 		[in] 开始时间 
	lpStopTime 			[in] 结束时间 
	sSavedFileName 		[in] 下载后保存到PC机的文件路径 


Return Values
	0表示失败，其他值作为JASDK_PlayBack_StopGetFile等函数的参数。获取错误码调用JASDK_GetLastError
Remarks
	预览的时候不可以保存，保存的时候不可以预览。想要保存就回调自己保存文件。


*/
LONG __stdcall JASDK_PlayBack_GetFileByTime(int lUserID, int lChannel, LPJASDK_PLAYBACK_TIME lpStartTime, LPJASDK_PLAYBACK_TIME lpStopTime, char *sSavedFileName);

/*
停止保存录象数据。

Parameters
	lPlayHandle 		[in] 播放句柄，JASDK_GetFileByTime 和 JASDK_GetFileByName的返回值 

Return Values
	TRUE表示成功，FALSE表示失败。获取错误码调用JASDK _GetLastError
*/
BOOL __stdcall JASDK_PlayBack_StopGetFile(int lFileHandle);


//录像回放抓图
/*

录像回放时抓图，并保存在文件中。

Parameters
	lPlayHandle 	[in] 播放句柄，JASDK_PlayBackByTime的返回值 
	sFileName 		[in] 保存图片数据的文件路径 

Return Values		TRUE表示成功，FALSE表示失败。获取错误码调用JASDK_GetLastError

See Also
	JASDK_PlayBackByTime  或 JASDK_PlayBackByName

*/
BOOL __stdcall JASDK_PlayBackCaptureFile(LONG lPlayHandle,char *sFileName);

/**
 *  P2P云台控制
 *
 *  @param p2p_handle 已经连接的P2P句柄,JASDK_Login的返回值
 *  @param nChannel   云台操作通道号
 *  @param act        云台操作动作
 *  @param bStart     1,云台动作开始;0,云台操作停止
 *  @param param1     云台操作参数1
 *  @param param2     云台操作参数2
 *
 *  @return TRUE:		操作成功
 *			FALSE：		操作超时
 */

int __stdcall JASDK_PTZ_CTRL(LONG lUserID, int nChannel,int act, int bStart, int param1,int param2);

#endif
