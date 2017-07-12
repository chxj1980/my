#include "ps_utils.h"
#include "wmpp.h"

//UDP client
//client send string to server

//Visual C++ 6.0

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

#define BUFLEN 1024
SOCKET soc;
SOCKADDR_IN addr;
WMPP wmpp_ = 0;
#define  nPort 4066
void s_OnReceived(
	WMPP h,
	const PACKET* pkt,
	const char* ip,
	unsigned short port,
	void* ctx)
{

}
int Create()
{
	WMPP_Init();
	if(wmpp_)
		return 0;

	wmpp_=WMPP_Create(WMPP_UDP_ClIENT);
	if(!wmpp_)
		return -1;

	WMPP_SetCallback(wmpp_,WMPP_CBF_RECEIVED,s_OnReceived,0);
	unsigned int bufsize = 1024*1024;
	WMPP_SetOption(wmpp_,WMPP_OPT_RECV_BUFFSIZE,&bufsize,sizeof(bufsize));
	WMPP_SetOption(wmpp_,WMPP_OPT_SEND_BUFFSIZE,&bufsize,sizeof(bufsize));
	int r=WMPP_Start(wmpp_,NULL,0,WMPP_GetCpuCount()*2+2);
	if(r!=0)
	{
		WMPP_Close(wmpp_);
		return r;
	}

	return 0;
}
void socketInit()
{
	int ret = Create();
}
int  SendDataBuf(char* pdata,int datalen)
{
	static bool bSocketInit = 0;
	if (bSocketInit == 0)
	{
		bSocketInit = 1;
		socketInit();
	}
	Sleep(10);
	return WMPP_Send1(wmpp_, pdata, datalen, "10.8.114.12",nPort);
}
uint16_t u16CSeq = 0;
uint32_t u32Ssrc = 1;
int gb28181_send_rtp_pack(char *databuff, int nDataLen, int mark_flag, uint64_t s64CurPts)
{
	int nRes = 0;
	int nPlayLoadLen = 0;
	int nSendSize    = 0;
	char szRtpHdr[RTP_HDR_LEN];
	memset(szRtpHdr, 0, RTP_HDR_LEN);
	char szBuff[RTP_MAX_PACKET_BUFF + 10];

	if(nDataLen + RTP_HDR_LEN <= RTP_MAX_PACKET_BUFF)// 1460 pPackerָ�뱾����һ��1460��С��buffer���ݻ���
	{
		// һ֡���ݷ�����󣬸�mark��־λ��1
		gb28181_make_rtp_header(szRtpHdr, 1, u16CSeq, (s64CurPts ), u32Ssrc);
		memcpy(szBuff, szRtpHdr, RTP_HDR_LEN);
		memcpy(szBuff + RTP_HDR_LEN, databuff, nDataLen);
		int nRet = SendDataBuf(szBuff, RTP_HDR_LEN + nDataLen);
		u16CSeq ++;

	}
	else 
	{
		nPlayLoadLen = RTP_MAX_PACKET_BUFF - RTP_HDR_LEN; // ÿ��ֻ�ܷ��͵����ݳ��� ��ȥrtpͷ
		gb28181_make_rtp_header(szBuff, 0, u16CSeq, (s64CurPts), u32Ssrc);
		memcpy(szBuff + RTP_HDR_LEN, databuff, nPlayLoadLen);
		int nRet = SendDataBuf(szBuff, RTP_HDR_LEN + nPlayLoadLen);
		u16CSeq ++;
		nDataLen -= nPlayLoadLen;
		// databuff += (nPlayLoadLen - RTP_HDR_LEN);
		databuff += nPlayLoadLen; // ����ǰ�浽�����Ѿ����ͳ�ȥ 		
		while(nDataLen > 0)
		{
			char* tmp = (databuff - RTP_HDR_LEN); // �������rtpͷ
			if(nDataLen <= nPlayLoadLen)
			{
				//һ֡���ݷ����꣬��mark��־λ
				gb28181_make_rtp_header(tmp, 1, u16CSeq, (s64CurPts), u32Ssrc);
				nSendSize = nDataLen;
			}
			else 
			{
				gb28181_make_rtp_header(tmp, 0, u16CSeq, (s64CurPts), u32Ssrc);
				nSendSize = nPlayLoadLen;
			}
			int nRet = SendDataBuf(tmp, RTP_HDR_LEN + nSendSize);
			nDataLen -= nSendSize;
			databuff += nSendSize ; 
			u16CSeq ++;
			//��Ϊbufferָ���Ѿ�����ƶ�һ��rtpͷ���Ⱥ�
			//����ÿ��ѭ������rtp��ʱ��ֻҪ��ǰ�ƶ������ݵ����ȼ��ɣ�����bufferָ��ʵ��ָ��λ����
			//databuff����ظ���rtp���ȵ������ݵ�λ���� 

		}

	}
	return 0;
}

uint32_t get_byte32(char* val)
{
	uint8_t val1 = (*val++);
	uint8_t val2 = (*val++);
	uint8_t val3 = (*val++);
	uint8_t val4 = (*val);
	uint32_t retVal = val1<<24|
		val2<<16|
		val3<<8|
		val4;
	return retVal;
}
int ParseFlvToH264Nal( char* nalsbuf, int nalsize,int* bneedparam,int bkye)
{
	char h264Statecode[] = {0x00,0x00,0x00,0x01};
	char* pnalcur = nalsbuf;
	*bneedparam = 1;
	while(nalsize >= 4)
	{
		unsigned int size = get_byte32(pnalcur);
		int ntype = 0;
		memcpy(pnalcur,h264Statecode,4);
		ntype = (*(pnalcur+4))&0x1f;
		if(ntype == 0x07 || ntype == 0x08||ntype == 0x01)
		{
			*bneedparam = 0;
		}
		if (ntype == 0x05 ||ntype == 0x07 || ntype == 0x08)
		{
			bkye = 1;
		}

		if (nalsize <= size + 4)
		{
			return 0;
		}	
		nalsize -= (size + 4);
		pnalcur += (size + 4);

	}
	return 1;
}


char* Psbuf = 0; 
int SendRtpPsToServer(char* spsbuf,int spslen, uint8_t* flvbuf,uint32_t flvsize,int tic)
{
	if (Psbuf == 0)
	{
		Psbuf = new char[1024*1024];
	}
	int bkey = (*flvbuf == 0x17)?1:0;
	int H264len = 0;
	int bneedspspps = 0;
	char* h264Start = Psbuf + PES_HDR_LEN;
	if (bkey)
	{
		H264len = spslen + flvsize - 5;
		memcpy(h264Start,spsbuf,spslen);
		memcpy(h264Start + spslen,flvbuf + 5,flvsize - 5);
		ParseFlvToH264Nal(h264Start + spslen,flvsize - 5,&bneedspspps,bkey);
	}
	else
	{
		H264len =  flvsize - 5;
		memcpy(h264Start,flvbuf + 5,flvsize - 5);
		ParseFlvToH264Nal(h264Start ,flvsize - 5,&bneedspspps,bkey);
	}
	

	
	char szTempPacketHead[256];
	int  nSizePos = 0;
	int  nSize = 0;		
	char *pBuff = NULL;
	__int64 s64CurPts = tic*90;
	memset(szTempPacketHead, 0, 256);
	// 1 package for ps header 
	gb28181_make_ps_header(szTempPacketHead + nSizePos, s64CurPts);
	nSizePos += PS_HDR_LEN;	
	//2 system header 
	if( bkey == 1 )
	{
		// �����I֡�Ļ��������ϵͳͷ
		gb28181_make_sys_header(szTempPacketHead + nSizePos);
		nSizePos += SYS_HDR_LEN;
		//����ط����ǲ�����I֡����p֡��������map�ģ�ò��ֻ��I֡��Ҳû������
		//		gb28181_make_psm_header(szTempPacketHead + nSizePos);
		//		nSizePos += PSM_HDR_LEN;

	}
	// psmͷ (Ҳ��map)
	gb28181_make_psm_header(szTempPacketHead + nSizePos);
	nSizePos += PSM_HDR_LEN;
	gb28181_send_rtp_pack(szTempPacketHead, nSizePos, 0,s64CurPts);
		



	// ��������ƶ���Ϊ�˷��㿽��pesͷ
	//������Ϊ�˼��ٺ�������Ƶ�����ݵĴ��������˷ѿռ䣬�������������ƶ�����ʵ�ʴ����ʱ��Ҫע���ַ�Ƿ�Խ���Լ����ǵ�����
	
	while(H264len > 0)
	{
		pBuff = (char*)h264Start - PES_HDR_LEN;
		//ÿ��֡�ĳ��Ȳ�Ҫ����short���ͣ����˾͵÷�Ƭ��ѭ���з���
		nSize = (H264len > 0xFFFF) ? 0xFFFF : H264len;
		// ���pesͷ
		gb28181_make_pes_header(pBuff, 0xE0 , nSize, (s64CurPts), (s64CurPts));

		gb28181_send_rtp_pack(pBuff, H264len + PES_HDR_LEN, 0,s64CurPts);
				

		//��Ƭ��ÿ�η��͵������ƶ�ָ�����
		H264len -= H264len;
		//����Ҳֻ�ƶ�nSize,��Ϊ��while����ƶ���pesͷ���ȣ������������pesͷ����
		h264Start   += H264len;

	}
	return 1;


}

