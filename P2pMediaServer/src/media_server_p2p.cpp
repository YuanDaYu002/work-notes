/*********************************************************************************
  *FileName: media_server_p2p.cpp
  *Create Date: 2018/09/06
  *Description: 本文件是p2p函数定义文件，基于shangyun SDK进行封装。 
  *Others:  
  *History:  
**********************************************************************************/
#include "PPCS_API.h"
#include "PPCS_Error.h"
#include "PPCS_Type.h"
#include "media_server_p2p.h"

 
 //init
int p2p_init()
{
	//初始化p2p连接参数句柄
	p2p_init_t handle;
	handle.DID = DID;
	handle.APILicense = APILICENSE;
	handle.CRCKey = CRCKEY;
	handle.InitString = INITSTRING;
	handle.WakeupKey = WAKEUPKEY;
	handle.IP1 = WAKEUP_SERVER1_IP;

	// 1. get P2P API Version
	UINT32 APIVersion = PPCS_GetAPIVersion();
	st_info("P2P API Version: %d.%d.%d.%d\n",
							(APIVersion & 0xFF000000)>>24, 
							(APIVersion & 0x00FF0000)>>16, 
							(APIVersion & 0x0000FF00)>>8, 
							(APIVersion & 0x000000FF)>>0);

	// 2. P2P Initialize
	PPCS_Initialize((char *)InitString);



}

//connect
int p2p_conect()
{
	// 3. Network Detect
	PPCS_NetworkDetect(&NetInfo, 0);

}

//listen
int p2p_listen()
{

}

//recv
int p2p_recv(void *handle,void*buf,int length)
{


}

//send
int p2p_send(void *handle,const void*data,int length)
{

}

//close
int p2p_close(void *handle)
{

}