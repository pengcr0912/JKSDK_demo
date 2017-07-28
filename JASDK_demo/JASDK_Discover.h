#ifndef __JASDK_DISCOVER_H__
#define __JASDK_DISCOVER_H__

typedef enum PWD_TYPE{
	PWD_TYPE_NONE,
	PWD_TYPE_MD5,
}enPWD_TYPE;


typedef char CHAR;
typedef void* Handler;
typedef void* LPVOID;

typedef enum SearchType{
	JASDK_ALL = 0,
	JASDK_IPC =1 << 0,
	JASDK_NVR =1 << 1,
	JASDK_DVR =1 << 2,
}SearchType_t;

typedef struct JASDKSearchItem{
	CHAR name[32];
	CHAR device_model[32];
	CHAR device_scope[128];
	CHAR esee_id[32];
	CHAR ip[32];
	CHAR port[32];
	CHAR ch_num[4];
	CHAR http_port[16];
	CHAR netmask[32];
	CHAR gateway[32];
	CHAR device_id[64];
	CHAR mac[32];
	CHAR hardware_version[32];
	CHAR software_version[32];
	CHAR JASDK_version[32];
	CHAR factory_Info[256];
	enPWD_TYPE password_type;
}stJASDKSearchItem,*pstJASDKSearchItem;

enum JASDKSetIPStatus{
	SETIP_STATUS_OK,
	SETIP_STATUS_ERROR,
};

typedef struct JASDKSetIPItemStatus
{
	int status;
	CHAR ip[32];
	CHAR netmask[32];
	CHAR gateway[32];
	CHAR device_id[64];
	CHAR mac[24];
}stJASDKSetIPItem,*pstJASDKSetIPItem;



typedef struct JASDK_setup_ip_info{
	CHAR  device_id[64];
	CHAR  device_username[36];
	CHAR  device_password[36];
	CHAR  device_ip[16];
	CHAR  device_netmask[16];
	CHAR  device_name[32];
	CHAR  device_gateway[16];
	CHAR  http_port[8];
	CHAR  device_mac[24];
	enPWD_TYPE  device_password_type;
}stJASDK_SETUP_IP_INFO,*pstJASDK_SETUP_IP_INFO;

/*
* 设备上下线通知
*/
typedef enum JASDKHelloByeDevice{
	DEVICE_HELLO,
	DEVICE_BYE
}JASDKHelloByeStatus;

typedef struct JASDKHelloByeItem{
	CHAR device_id[64];
	CHAR device_name[32];
	CHAR device_model[32];
	CHAR device_ip[32];
	CHAR device_mac[24];
	JASDKHelloByeStatus status;
}stJASDKHelloByeItem,*pstJASDKHelloByeItem;


/*
回调函数
有搜索到服务端时，调用此函数。
info  为服务端信息

*/
typedef const void ( *notify_Search_Handle)(pstJASDKSearchItem info, LPVOID pUser);
typedef const void ( *notify_SetIP_Handle)(pstJASDKSetIPItem info, LPVOID pUser);
typedef const void ( *notify_Hello_Bye_Handle)(pstJASDKHelloByeItem info, LPVOID pUser);


/*
*需要回调的函数，客户自己实现。
*  search_handle
*
*
*/
typedef struct JASDK_Search_Proc{
	notify_Search_Handle search_handle;
	notify_SetIP_Handle  setip_handle;
	notify_Hello_Bye_Handle hb_handle;
}stJASDK_Search_Proc,*pstJASDK_Search_Proc;


/*
开始搜索
handler             JASDK句柄
type                 要搜索类型
scope               搜索属性
n                     搜索次数
*/
int JASDK_Search_Start(Handler handler, SearchType_t type, char* scope ,int n);

/*
停止搜索
*/
void JASDK_Search_Stop(Handler h);

/*
设置指定IP，组播形式
*/
int JASDK_SetupIP(Handler handler,stJASDK_SETUP_IP_INFO info);

//////////////////////////////////////////////////////////////////

typedef struct JASDK_SEARCH_INIT{
	char *local_ip;      							//本机IP
	char *broadcast_ip;          					//广播地址
	stJASDK_Search_Proc search_proc;			//客户端回调
//	stJASDK_CONF_FUNC conf_func;				//服务端回调
	LPVOID pUser;								//用户自己的信息
}stJASDK_Search_Init, *pstJASDK_Search_Init;

 /*
JASDK的初始化
Handler：     返回值，JASDK句柄。
*/
extern Handler JASDK_Search_init(pstJASDK_Search_Init search_init);
extern void JASDK_Search_destroy(Handler handler);

#endif