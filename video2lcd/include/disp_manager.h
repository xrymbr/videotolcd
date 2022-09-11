
#ifndef _DISP_MANAGER_H
#define _DISP_MANAGER_H


#include <pic_operation.h>
#include <video_manager.h>


typedef struct DispOpr{
	char *name; 			 /* ��ʾģ������� */
	int iXres;				 /* X�ֱ��� */
	int iYres;				 /* Y�ֱ��� */
	int iBpp;				 /* һ�������ö���λ����ʾ */
	int iLineWidth; 		 /* һ������ռ�ݶ����ֽ� */
	unsigned char *pucDispMem;	 /* �Դ��ַ */
	int (*DeviceInit)(void);     /* �豸��ʼ������ */
	int (*ShowPixel)(int iPenX, int iPenY, unsigned int dwColor);    /* ��ָ�������������Ϊĳ��ɫ */
	int (*CleanScreen)(unsigned int dwBackColor);                    /* ����Ϊĳ��ɫ */
	int (*ShowPage)(PT_PixelDatas ptPixelDatas);                         /* ��ʾһҳ,����Դ��ptVideoMem */
	struct DispOpr *ptNext;      /* ���� */
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
