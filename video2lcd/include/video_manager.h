#ifndef _VIDEO_MANAGER_H
#define _VIDEO_MANAGER_H

#include <config.h>
#include <pic_operation.h>
#include <linux/videodev2.h>


#define NB_BUFFER 1

struct Video_Device;
struct VideoOpr;
typedef struct Video_Device T_VideoDevice, *PT_VideoDevice;
typedef struct VideoOpr T_VideoOpr, *PT_VideoOpr;


typedef struct Video_Device {
	int iFd; 		 //文件句柄
	int iPixeformat; //像素格式
	int iWidth;		 //分辨率宽
	int iHeight;	 //分辨率高

	int iVideoBufCnt;		//buf数量
	int iVideoBufMaxLen;	//buf最大长度
	int iVideoBufCurIndex;	//当前buf索引
	unsigned char *pucVideoBuf[NB_BUFFER]; //每个videobuf的地址 

	PT_VideoOpr ptOPr;
	
} T_VideoDevice, *PT_VideoDevice;


typedef struct VideoBuf {
	T_PixelDatas tPixelDatas;
	int iPixelFormat;
}T_VideoBuf,*PT_VideoBuf;


typedef struct VideoOpr {
	char *name;
	int (*InitDevice)(char *strDevName,PT_VideoDevice ptVideoDevice);
	int (*ExitDevice)(PT_VideoDevice ptVideoDevice);
	int (*GetFormat)(PT_VideoDevice ptVideoDevice);
	int (*GetFrame)(PT_VideoDevice ptVideoDevice,PT_VideoBuf ptVideoBuf);
	int (*PutFrame)(PT_VideoDevice ptVideoDevice,PT_VideoBuf ptVideoBuf);
	int (*StartDevice)(PT_VideoDevice ptVideoDevice);
	int (*StopDevice)(PT_VideoDevice ptVideoDevice);

	struct VideoOpr *ptNext;
}T_VideoOpr,*PT_VideoOpr;


int VideoDeviceInit(char *strDevName, PT_VideoDevice ptVideoDevice);
int V4l2Init(void);
int RegisterVideoOpr(PT_VideoOpr ptVideoOpr);
int VideoInit(void);

#endif
