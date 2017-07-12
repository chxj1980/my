#pragma once



#ifdef __cplusplus
extern "C"
{
#endif

typedef void* WMPP;

//�������
#define WMPP_TCP_SERVER		1
#define WMPP_TCP_SESSION	2
#define WMPP_TCP_CLIENT		3
#define WMPP_UDP_HANDLE		4
#define WMPP_SSL_SERVER		5
#define WMPP_SSL_CLIENT		6
#define WMPP_UDP_ClIENT		7


//ѡ������
#define WMPP_OPT_MAXSENDQUEUE	1	//���÷��Ͷ��е��������
#define WMPP_OPT_MAXRECVBUFF	2	//���������ջ�����,���������С��Ȼ���ܽ������Ļ�ǿ�ƶϿ�����
#define WMPP_OPT_RECVTIMEOUT	3	//���ý��ճ�ʱ,�������ʱ��û�н��յ����ݻ�ǿ�ƶϿ�����
#define WMPP_OPT_WORKS			4	//���ù����߳���
#define WMPP_OPT_RECV_BUFFSIZE	5	//���ջ�����
#define WMPP_OPT_SEND_BUFFSIZE	6	//���ͻ�����







//���Ľṹ��
typedef struct _PACKET
{
	unsigned int cmd;		//��������
	unsigned int result;	//���Ĵ�����
	unsigned int sequence;	//������ˮ��
	const char* pbody;		//��������
	unsigned int body_size;	//�������ݳ���
}PACKET;





//�ص�����
#define WMPP_CBF_ACCEPTED		1
#define WMPP_CBF_RECEIVED		2
#define WMPP_CBF_CLOSED			3

typedef void (*WMPP_CBF_Accepted)(WMPP h,const char* ip,unsigned short port,void* ctx);
typedef void (*WMPP_CBF_Received)(WMPP h,const PACKET* pkt,const char* ip,unsigned short port,void* ctx);
typedef void (*WMPP_CBF_Closed)(WMPP h,unsigned long nError,const char* ip,unsigned short port,void* ctx);



#ifdef __cplusplus
}
#endif



