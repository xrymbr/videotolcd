
#include <config.h>
#include <disp_manager.h>
#include <string.h>

static PT_DispOpr g_ptDispOprHead;
static PT_DispOpr g_ptDefaultDispOpr;

/**********************************************************************
 * �������ƣ� RegisterDispOpr
 * ���������� ע��"��ʾģ��", ������֧�ֵ���ʾ�豸�Ĳ���������������
 * ��������� ptDispOpr - һ���ṹ��,�ں���ʾ�豸�Ĳ�������
 * ��������� ��
 * �� �� ֵ�� 0 - �ɹ�, ����ֵ - ʧ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/
int RegisterDispOpr(PT_DispOpr ptDispOpr)
{
	PT_DispOpr ptTmp;

	if (!g_ptDispOprHead)
	{
		g_ptDispOprHead   = ptDispOpr;
		ptDispOpr->ptNext = NULL;
	}
	else
	{
		ptTmp = g_ptDispOprHead;
		while (ptTmp->ptNext)
		{
			ptTmp = ptTmp->ptNext;
		}
		ptTmp->ptNext	  = ptDispOpr;
		ptDispOpr->ptNext = NULL;
	}

	return 0;
}


/**********************************************************************
 * �������ƣ� ShowDispOpr
 * ���������� ��ʾ��������֧�ֵ�"��ʾģ��"
 * ��������� ��
 * ��������� ��
 * �� �� ֵ�� ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/
void ShowDispOpr(void)
{
	int i = 0;
	PT_DispOpr ptTmp = g_ptDispOprHead;

	while (ptTmp)
	{
		printf("%02d %s\n", i++, ptTmp->name);
		ptTmp = ptTmp->ptNext;
	}
}





/**********************************************************************
 * �������ƣ� GetDispOpr
 * ���������� ��������ȡ��ָ����"��ʾģ��"
 * ��������� pcName - ����
 * ��������� ��
 * �� �� ֵ�� NULL   - ʧ��,û��ָ����ģ��, 
 *            ��NULL - ��ʾģ���PT_DispOpr�ṹ��ָ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/


PT_DispOpr GetDispOpr(char *pcName)
{
	PT_DispOpr ptTmp = g_ptDispOprHead;
	
	while (ptTmp)
	{
		if (strcmp(ptTmp->name, pcName) == 0)
		{
			return ptTmp;
		}
		ptTmp = ptTmp->ptNext;
	}
	return NULL;
}


/**********************************************************************
 * �������ƣ� SelectAndInitDefaultDispDev
 * ���������� ��������ȡ��ָ����"��ʾģ��", �������ĳ�ʼ������, ��������
 * ��������� name - ����
 * ��������� ��
 * �� �� ֵ�� ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/

void SelectAndInitDefaultDispDev(char *name)
{
	g_ptDefaultDispOpr = GetDispOpr(name);
	if (g_ptDefaultDispOpr)
	{
		g_ptDefaultDispOpr->DeviceInit();
		g_ptDefaultDispOpr->CleanScreen(0);
	}
}


/**********************************************************************
 * �������ƣ� GetDefaultDispDev
 * ���������� ����������SelectAndInitDefaultDispDevѡ������ʾģ��,
 *            ���������ظ���ʾģ��
 * ��������� ��
 * ��������� ��
 * �� �� ֵ�� ��ʾģ���PT_DispOpr�ṹ��ָ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/
PT_DispOpr GetDefaultDispDev(void)
{
	return g_ptDefaultDispOpr;
}

/**********************************************************************
 * �������ƣ� GetDispResolution
 * ���������� �����ʹ�õ���ʾ�豸�ķֱ��ʺ�BPP
 * ��������� ��
 * ��������� piXres - ��X�ֱ���
 *            piYres - ��X�ֱ���
 *            piBpp  - ��BPP
 * �� �� ֵ�� 0  - �ɹ�
 *            -1 - ʧ��(δʹ��SelectAndInitDefaultDispDev��ѡ����ʾģ��)
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/
int GetDispResolution(int *piXres, int *piYres, int *piBpp)
{
	if (g_ptDefaultDispOpr)
	{
		*piXres = g_ptDefaultDispOpr->iXres;
		*piYres = g_ptDefaultDispOpr->iYres;
		*piBpp	= g_ptDefaultDispOpr->iBpp;
		return 0;
	}
	else
	{
		return -1;
	}
}


int GetVideoBufForDisplay(PT_VideoBuf ptFrameBuf)
{
    ptFrameBuf->iPixelFormat = (g_ptDefaultDispOpr->iBpp == 16) ? V4L2_PIX_FMT_RGB565 : \
                                   (g_ptDefaultDispOpr->iBpp == 32) ?  V4L2_PIX_FMT_RGB32 : \
                                           0;
    ptFrameBuf->tPixelDatas.iWidth  = g_ptDefaultDispOpr->iXres;
    ptFrameBuf->tPixelDatas.iHeight = g_ptDefaultDispOpr->iYres;
    ptFrameBuf->tPixelDatas.iBpp    = g_ptDefaultDispOpr->iBpp;
    ptFrameBuf->tPixelDatas.iLineBytes    = g_ptDefaultDispOpr->iLineWidth;
    ptFrameBuf->tPixelDatas.iTotalBytes   = ptFrameBuf->tPixelDatas.iLineBytes * ptFrameBuf->tPixelDatas.iHeight;
    ptFrameBuf->tPixelDatas.aucPixelDatas = g_ptDefaultDispOpr->pucDispMem;
    return 0;
}


void FlushPixelDatasToDev(PT_PixelDatas ptPixelDatas)
{
    g_ptDefaultDispOpr->ShowPage(ptPixelDatas);
}

/**********************************************************************
 * �������ƣ� DisplayInit
 * ���������� ע����ʾ�豸
 * ��������� ��
 * ��������� ��
 * �� �� ֵ�� 0 - �ɹ�, ����ֵ - ʧ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/
int DisplayInit(void)
{
	int iError;
	
	iError = FBInit();

	return iError;
}



