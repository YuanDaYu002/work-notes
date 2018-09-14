/*********************************************************************************
  *FileName: media_server_interface.h
  *Create Date: 2018/09/05
  *Description: 本文件为设备media server 和设备端app软件交互的接口定义。 
  *Others:  
  *History:  
**********************************************************************************/
#ifndef MEDIA_SERVER_INTERFACE_H
#define MEDIA_SERVER_INTERFACE_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

key_t msg_queue_key;				//消息队列键值（设备端app和media server 之间进行通信,media_server_init会初始化）。

enum P2P_media_server_status
{
	sleeping = 0,		//睡眠状态（无客户端连接）
	waked = 1,			//唤醒状态（无客户端连接）
	connected,			//客户端已连接状态
	livingstream,		//实时流传输状态
	upgrade,			//升级状态
	
};


enum med_ser_error_code
{
	media_ser_offline = -3,
	media_ser_param_err = -2,		//参数错误
	media_ser_error  = -1,
	media_ser_success = 0,

};

enum med_ser_alarm_file_type
{
	JPEG_file = 0,
	H264_video_file = 1,
	H265_video_file = 2,
	g711_audio_file = 3,
	H264_mix_g711_file = 4,
	H265_mix_g711_file = 5,
};

enum med_ser_device_type
{
	HI3516C_V300_IPC = 0,
	HI3516E_V100_IPC = 1,
};

typedef struct _med_ser_alarm_file_t
{
    	char  file_type;			//告警文件类型，赋值参考enum media_server_alarm_file_type
    	char  alarm_level;			//告警等级，待定
   		char  is_finished;			//是否已经记录完成（完整的文件）
    	char  reserved;				//字节对齐，占位
    	int   file_size;			//告警文件大小
    	char  create_date[32];		//文件创建日期，格式：2018/09/05
    	char  create_time[32];		//文件创建时间，格式：00:00-24:00, 24小时制
    	char  finish_time[32];		//文件记录结束时间，格式：00:00-24:00, 24小时制
    	char  file_path[96];		//文件路径

} med_ser_alarm_file_t;


typedef struct _med_ser_alarm_push_condition_t 
{
	//待定,告警信息，告警发生的位置、时长、面积比、速度等信息
	//以及告警发生时要不要降低码率，减小录制的告警文件大小、码率多长时间恢复等
        char   if_push_to_app;	//是否推送到手机APP，1：推送  0：不推送
	med_ser_alarm_file_t push_file;

}med_ser_alarm_push_condition_t;

typedef struct _device_id_t
{
	char 	mac[6];
	char 	reserve[2];
	char	deviceid[16];

}device_id_t;

typedef struct _med_ser_init_info_t
{
	unsigned int 	device_type;				//设备类型,参考enum med_ser_device_type;
	unsigned int 	device_capacity;			//设备能力位，设备支持的功能属性；
	unsigned int	device_video_channel_num;	//设备的视频通道数；
	unsigned int 	use_wireless_network;		//设备是无线的还是有线，1：无线，0：有线
	const char 		*device_id;					//设备id；
	const char 		*device_name;				//设备名；
	const char 		*config_dir;				//配置文件路径；
	const char 		*uboot_version;
	const char 		*kernel_version;
	const char 		*rootfs_version;
	const char 		*app_version;
	const char 		*network_interface;			//网卡名称 wlan0, ra0, eth0 ...；
	const char 		*high_resolution;			//主码流(高清)的分辨率,格式:1920*1080;
	const char 		*secondary_resolution;		//次码流(普清)的分辨率,格式:1280*720;
	const char 		*low_resolution;			//低码流(低清)的分辨率,格式:640*480;
	
	/*服务器返回时间戳校时，回调函数*/
	void (*timing_callback)(time_t timestamp);

	/*设备上线会回调该函数，告知设备软件设备已上线*/
	void (*device_is_online_callback)(int status);
	
	/*告警的推送策略设置接口,服务器下发的告警策略，media server 会调用该接口进行设置
 	  @condition:策略
 	  @condition_count:策略的条数
 	*/
	void (*set_push_condition_callback)(med_ser_alarm_push_condition_t *condition,int condition_count);
	

	/*
  	  临时设置或者恢复码流的帧率和码率
 	  @type: 1为临时设置，0为恢复默认
 	  @stream_type: 码流类型，2是HD，1是MD，0是LD
 	  @frame_rate: 当type为1时，表示码流帧率
 	  @bit_rate: 当type为1时，表示码流码率，单位Kbit		
	*/
	void (*set_stream_temporary_callback)(int type, int stream_type, int frame_rate, int bit_rate);	
	
	/*
 	  临时设置或者恢复码流的gop
  	  @type: 1为临时设置，0为恢复默认
 	  @gop: I帧间隔,1~10S
 	*/
	void (*on_set_stream_gop_callback)(int type, int gop);

	/*
	 一系列获取帧返回的接口
	 @channel: 通道, 0:1920*1080P , 1:1280*720P
	 @frame_addr:帧地址
	 @length: 帧长度 
	*/
	int (*get_one_YUV_frame_callback )(int channel,const void*frame_addr,int length);
	int (*get_one_H264_frame_callback)(int channel,const void*frame_addr,int length);
	int (*get_one_H265_frame_callback)(int channel,const void*frame_addr,int length);
	int (*get_one_JPEG_frame_callback)(const void*frame_addr,int length);
	int (*get_one_g711_frame_callback)(const void*frame_addr,int length);
	int (*get_one_g726_frame_callback)(const void*frame_addr,int length);
	int (*get_one_PCM_frame_callback )(const void*frame_addr,int length); 

	/*
	 获取一个编码帧返回（实时流传输）。
	 	考虑编码后的缓存buffer，如果视频帧和audio帧是在一个大buffer中均匀混合的，
	 	media server就不区分是音频帧还是视频帧,在传输实时流也不需要去区分。
	 @channel: 通道, 0:1920*1080P , 1:1280*720P
	 @frame_addr:帧地址
	 @length: 帧长度 
	*/
	int (*get_one_encoded_frame_callback)(int channel,const void*frame_addr,int length);

	int (*set_device_id_callback)(device_id_t*data,int length);

}med_ser_init_info_t;


/*********************************************************************
 *函数名：media_server_init
 *功能：初始化媒体服务器
 *参数：
 *返回值：
 *	成功：media_server_success
 *	失败：media_server_error
 * ******************************************************************/
int media_server_init(med_ser_init_info_t* info, unsigned int info_len);


/*********************************************************************
 *函数名：media_server_start
 *功能：启动媒体服务器
 *参数：
 *返回值：
 *	成功：media_server_success
 *	失败：media_server_error
 * ******************************************************************/
int media_server_start();


/*********************************************************************
 *函数名：media_server_get_server_timestamp
 *功能：获取服务器上的时间，用于设备校时
 *参数：无
 *返回值：
 *	成功：media_server_success
 *	失败：media_server_error（设备没有连接上服务器）
 * ******************************************************************/
int media_server_get_server_timestamp();


/*********************************************************************
 *函数名：media_server_if_upgrading
 *功能：判断是否在升级
 *参数：无
 *返回值：
 *	在升级状态：media_server_upgrading
 *	不在升级状态：media_server_success
 * ******************************************************************/
int media_server_if_upgrading();



#endif
 
