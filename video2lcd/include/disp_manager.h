
#ifndef _DISP_MANAGER_H
#define _DISP_MANAGER_H


#include <pic_operation.h>
#include <video_manager.h>


typedef struct DispOpr{
	char *name; 			 /* 显示模块的名字 */
	int iXres;				 /* X分辨率 */
	int iYres;				 /* Y分辨率 */
	int iBpp;				 /* 一个象素用多少位来表示 */
	int iLineWidth; 		 /* 一行数据占据多少字节 */
	unsigned char *pucDispMem;	 /* 显存地址 */
	int (*DeviceInit)(void);     /* 设备初始化函数 */
	int (*ShowPixel)(int iPenX, int iPenY, unsigned int dwColor);    /* 把指定座标的象素设为某颜色 */
	int (*CleanScreen)(unsigned int dwBackColor);                    /* 清屏为某颜色 */
	int (*ShowPage)(PT_PixelDatas ptPixelDatas);                         /* 显示一页,数据源自ptVideoMem */
	struct DispOpr *ptNext;      /* 链表 */
}T_DispOpr, *PT_DispOpr;


int RegisterDispOpr(PT_DispOpr ptDispOpr);
void ShowDispOpr(void);
PT_DispOpr GetDispOpr(char *pcName);
void SelectAndInitDefaultDispDev(char *name);
PT_DispOpr GetDefaultDispDev(void);
int GetDispResolution(int *piXres, int *piYres, int *piBpp);
int GetVideoBufForDisplay(PT_VideoBuf ptFrameBuf);
void FlushPixelDatasToDev(PT_PixelDatas ptPixelDatas);
int FBInit(void);
int DisplayInit(void);


#endif
