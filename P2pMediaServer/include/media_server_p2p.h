/*********************************************************************************
  *FileName: media_server_p2p.h
  *Create Date: 2018/09/06
  *Description: 本文件是p2p传输的头文件，基于shangyun SDK进行封装。 
  *Others:  
  *History:  
**********************************************************************************/
#ifndef MEDIA_SERVER_P2P_H
#definr MEDIA_SERVER_P2P_H

#define CH_CMD				0
#define CH_DATA				1
#define SERVER_NUM			3	// WakeUp Server Number
#define SIZE_DID 			30	// Device ID Size
#define SIZE_APILICENSE 	24	// APILicense Size
#define SIZE_INITSTRING 	256	// InitString Size
#define SIZE_WAKEUP_KEY 	17	// WakeUp Key Size

#define MAX_CLIENT_NUM 		16  //最大能同时接入的客户端数量

#define P2P_SUPORT_WAKEUP

#ifndef P2P_SUPORT_WAKEUP
//standard p2p 参数（不支持唤醒）
#define DID 				"PPCS-016947-YFYNG"
#define APILICENSE 			"BBEHHJ"
#define CRCKEY 				"EasyView"
#define INITSTRING 			"EBGAEIBIKHJJGFJKEOGCFAEPHPMAHONDGJFPBKCPAJJMLFKBDBAGCJPBGOLKIKLKAJMJKFDOOFMOBECEJIMM"

#else
//advanced p2p 参数（支持唤醒）
#define DID 				"RTOS-000236-STWDB"
#define APILICENSE 			"ATTWPQ"
#define CRCKEY 				"EasyView"
#define INITSTRING 			"EFGBFFBJKEJKGGJJEEGFFHELHHNNHONHGLFNBHCCAEJDLNLPDDAGCIOFGDLGJMLAAOMOKCDLOONOBICJJIMM "
#define WAKEUPKEY 			"1234567890ABCDEF"			
#define IP_LENGTH			16
#define TCP_PORT			12306
#define UDP_PORT			12305
char g_ServerIP[SERVER_NUM][IP_LENGTH] = {{"112.74.108.149"}{"112.74.108.149"}{"112.74.108.149"}};
#endif


typedef struct _p2p_handle_t
{
	char *DID;			 				//DID: This is Device ID, such as: ABCD-123456-ABCDEF
	char *APILicense;	 				//APILicense: If you set up CRCKey, this parameter must enter APILicense:CRCKey, if not, you only need to enter APILicense
	char *CRCKey;		 				//[CRCKey]
	char *InitString;	 				//tInitString: The encrypted string of the server IP address or the domain name.
	//unsigned int Repeat; 				//[Repeat]: The number of repeated calls to PPCS_Listen.
	char *WakeupKey; 	 				//[WakeupKey]: Wakeup Server String Key
	char IP[SERVER_NUM][IP_LENGTH];		//[IP1],[IP2],[IP3]: Three Wakeup Server IP or domain name, You need to enter at least one IP

	struct sockaddr_in serveraddr[SERVER_NUM];//build the server's Internet address
	int server_index;					//当前正建立连接的唤醒服务器在serveraddr数组中的下标
	int skt;							//和唤醒服务器建立TCP连接的socket。
	int Session_num;					//当前已经连接的会话数量（客户端数量）,不能大于MAX_CLIENT_NUM

}p2p_handle_t;


//init  初始化配置参数 + P2P初始化。
int p2p_init(p2p_handle_t *P2P_handle);

//connect
int p2p_conect(p2p_handle_t *P2P_handle);

//wakeup 
int P2P_wait_for_wakeup(p2p_handle_t *P2P_handle);


//listen
int p2p_listen(p2p_handle_t *P2P_handle);

//客户端任务入口函数（每个客户端接入。都会创建一个线程，专程处理该客户端的业务）。
int P2P_client_task_create(p2p_handle_t *P2P_handle,int SessionID);
int P2P_client_task_func(p2p_handle_t *P2P_handle,int SessionID);
//recv
int p2p_recv(void *handle,void*buf,int length);

//send
int p2p_send(void *handle,const void*data,int length);

//close
int p2p_close(void *handle); 


#endif

