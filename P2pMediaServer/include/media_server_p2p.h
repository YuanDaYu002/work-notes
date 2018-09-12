/*********************************************************************************
  *FileName: media_server_p2p.h
  *Create Date: 2018/09/06
  *Description: 本文件是p2p传输的头文件，基于shangyun SDK进行封装。 
  *Others:  
  *History:  
**********************************************************************************/
#ifndef MEDIA_SERVER_P2P_H
#definr MEDIA_SERVER_P2P_H

/*
Standard P2P（Linux）：
	NDT:(DID:NDTLicense)
	PPCS-016946-RZFDR:WPJMSP
	PPCS-016947-YFYNG:WJASBL
	PPCS-016948-UVLMV:JECQHC
	PPCS-016949-TRLKZ:DJBRFD
	PPCS-016950-YMLFM:CZBHPZ
*/
#define DID 				"PPCS-016946-RZFDR"
#define APILICENSE 			"WPJMSP"
#define CRCKEY 				"EasyView"
#define INITSTRING 			"EBGAEIBIKHJJGFJKEOGCFAEPHPMAHONDGJFPBKCPAJJMLFKBDBAGCJPBGOLKIKLKAJMJKFDOOFMOBECEJIMM"
#define WAKEUPKEY 			"1234567890ABCDEF"
#define WAKEUP_SERVER1_IP	"112.74.108.149"
#define TCP_PORT			12306
#define UDP_PORT			12305			

typedef struct _p2p_init_t
{
	char *DID;			 	//DID: This is Device ID, such as: ABCD-123456-ABCDEF
	char *APILicense;	 	//APILicense: If you set up CRCKey, this parameter must enter APILicense:CRCKey, if not, you only need to enter APILicense
	char *CRCKey;		 	//[CRCKey]
	char *InitString;	 	//tInitString: The encrypted string of the server IP address or the domain name.
	//unsigned int Repeat; 	//[Repeat]: The number of repeated calls to PPCS_Listen.
	char *WakeupKey; 	 	//[WakeupKey]: Wakeup Server String Key
	char *IP1;			 	//[IP1],[IP2],[IP3]: Three Wakeup Server IP or domain name, You need to enter at least one IP
	char *IP2;			 	
	char *IP3;			 	

}p2p_init_t;


//init
int p2p_init(void *handle);

//connect
int p2p_conect();

//listen
int p2p_listen();

//recv
int p2p_recv(void *handle,void*buf,int length);

//send
int p2p_send(void *handle,const void*data,int length);

//close
int p2p_close(void *handle); 


#endif

