#pragma once

#include "wmpp_def.h"


#ifdef __cplusplus
extern "C"
{
#endif

//��ʼ��
//return:WMP_OK��ʾ�ɹ�,���򷵻ش�����
int WMPP_Init();


//ע��
void WMPP_Cleanup();


//�������
//handle_type:�������
//return:�ɹ����ؾ��,ʧ�ܷ���0;
WMPP WMPP_Create(int handle_type);

//�رվ��
int WMPP_Close(WMPP h);



//����/��ȡѡ��
//h:���
//opt:ѡ�����
//optval:Ҫ����ֵ��ָ��
//opts:optval�ĳ���
//return:WMP_OK��ʾ�ɹ�,���򷵻ش�����
int WMPP_SetOption(WMPP h,int opt,void* optval,unsigned int opts);
int WMPP_GetOption(WMPP h,int opt,void* optval,unsigned int opts);


//���ûص�
//h:���
//flag:�ص�����
//cbf:�ص�������ַ
//ctx:�����Ĳ���
//return:WMP_OK��ʾ�ɹ�,���򷵻ش�����
int WMPP_SetCallback(WMPP h,int flag,void* cbf,void* ctx);



//����
//h:���
//host:Ŀ���ַ,����������
//port:Ŀ��˿�
//works:�����߳���
//return:WMP_OK��ʾ�ɹ�,���򷵻ش�����
int WMPP_Start(WMPP h,const char* host,unsigned short port,unsigned int works);

//�ָ�����,TCP����
//h:���
//host:Ŀ���ַ,����������
//port:Ŀ��˿�
//return:WMP_OK��ʾ�ɹ�,���򷵻ش�����
int WMPP_Repair(WMPP h,const char* host,unsigned short port);

//ֹͣ�������,�������پ����Դ
int WMPP_Stop(WMPP h);

//����
//h:���
//pkt:���͵�����
//ip:���͵�Ŀ���ַ,TCP���Ժ��Ըò���
//port:���͵�Ŀ��˿�,TCP���Ժ��Ըò���
//return:WMP_OK��ʾ�ɹ�,���򷵻ش�����
int WMPP_Send(WMPP h,const PACKET* pkt,const char* ip,unsigned short port);

//����
//h:���
//pkt:���͵�����
//ip:���͵�Ŀ���ַ,TCP���Ժ��Ըò���
//port:���͵�Ŀ��˿�,TCP���Ժ��Ըò���
//return:WMP_OK��ʾ�ɹ�,���򷵻ش�����
int WMPP_Send1(WMPP h,const char* pdata,int datalen,const char* ip,unsigned short port);
//���Ͳ��ȴ���Ӧ
//h:���
//req:���͵�����
//rsp:��Ӧ������,�ýṹ���е�pbodyָ������ʱ��,���賤��ʹ�ñ������´ε���ǰ���临��.
//time_out:��ʱʱ��,��λ:����
//ip:���͵�Ŀ���ַ,TCP���Ժ��Ըò���
//port:���͵�Ŀ��˿�,TCP���Ժ��Ըò���
//return:WMP_OK��ʾ�ɹ�,���򷵻ش�����
int WMPP_SendWait(WMPP h,const PACKET* req,PACKET* rsp,unsigned int time_out,const char* ip,unsigned short port);

//��������,�����ȴ���Ӧ
//�ķ����ᱣ�������¼,ֱ������WMPP_RecvRspʱ���
//h:���
//req:���͵�����
//ip:���͵�Ŀ���ַ,TCP���Ժ��Ըò���
//port:���͵�Ŀ��˿�,TCP���Ժ��Ըò���
//return:WMP_OK��ʾ�ɹ�,���򷵻ش�����
int WMPP_SendReq(WMPP h,const PACKET* req,const char* ip,unsigned short port);

//��ȡ��WMPP_SendReq�����������
//h:���
//seq:WMPP_SendReq ����req�е���ˮ��,���ݴ���ˮ�Ž��ҵ���Ӧ�ļ�¼
//rsp:��Ӧ������,�ýṹ���е�pbodyָ������ʱ��,���賤��ʹ�ñ������´ε���ǰ���临��.
//time_out:��ʱʱ��,��λ:����
//return:WMP_OK��ʾ�ɹ�,���򷵻ش�����
int WMPP_RecvRsp(WMPP h,unsigned int seq,PACKET* rsp,unsigned int timeout);

//��ȡ��ǰ���Ͷ�������
//h:���
//c:�������
//return:WMP_OK��ʾ�ɹ�,���򷵻ش�����
int WMPP_GetSendQeueCount(WMPP h,unsigned int* c);

//��շ��ͻ�����
//h:���
//return:WMP_OK��ʾ�ɹ�,���򷵻ش�����
int WMPP_ClearSendQueue(WMPP h);





//��ȡCPU������
unsigned int WMPP_GetCpuCount();

//��ȡ������ˮ��
unsigned int WMPP_GetSequence(WMPP h);



#ifdef __cplusplus
}
#endif