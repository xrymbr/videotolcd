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
	int iFd; 		 //�ļ����
	int iPixeformat; //���ظ�ʽ
	int iWidth;		 //�ֱ��ʿ�
	int iHeight;	 //�ֱ��ʸ�

	int iVideoBufCnt;		//buf����
	int iVideoBufMaxLen;	//buf��󳤶�
	int iVideoBufCurIndex;	//��ǰbuf����
	unsigned char *pucVideoBuf[NB_BUFFER]; //ÿ��videobuf�ĵ�ַ 

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
