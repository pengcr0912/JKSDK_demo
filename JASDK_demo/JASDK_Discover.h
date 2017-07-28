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
* �豸������֪ͨ
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
�ص�����
�������������ʱ�����ô˺�����
info  Ϊ�������Ϣ

*/
typedef const void ( *notify_Search_Handle)(pstJASDKSearchItem info, LPVOID pUser);
typedef const void ( *notify_SetIP_Handle)(pstJASDKSetIPItem info, LPVOID pUser);
typedef const void ( *notify_Hello_Bye_Handle)(pstJASDKHelloByeItem info, LPVOID pUser);


/*
*��Ҫ�ص��ĺ������ͻ��Լ�ʵ�֡�
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
��ʼ����
handler             JASDK���
type                 Ҫ��������
scope               ��������
n                     ��������
*/
int JASDK_Search_Start(Handler handler, SearchType_t type, char* scope ,int n);

/*
ֹͣ����
*/
void JASDK_Search_Stop(Handler h);

/*
����ָ��IP���鲥��ʽ
*/
int JASDK_SetupIP(Handler handler,stJASDK_SETUP_IP_INFO info);

//////////////////////////////////////////////////////////////////

typedef struct JASDK_SEARCH_INIT{
	char *local_ip;      							//����IP
	char *broadcast_ip;          					//�㲥��ַ
	stJASDK_Search_Proc search_proc;			//�ͻ��˻ص�
//	stJASDK_CONF_FUNC conf_func;				//����˻ص�
	LPVOID pUser;								//�û��Լ�����Ϣ
}stJASDK_Search_Init, *pstJASDK_Search_Init;

 /*
JASDK�ĳ�ʼ��
Handler��     ����ֵ��JASDK�����
*/
extern Handler JASDK_Search_init(pstJASDK_Search_Init search_init);
extern void JASDK_Search_destroy(Handler handler);

#endif