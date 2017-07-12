#include "ps_utils.h"
#include <string>
static unsigned int crc32table1[256] = {   
	0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9, 0x130476dc, 0x17c56b6b,   
	0x1a864db2, 0x1e475005, 0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,   
	0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd, 0x4c11db70, 0x48d0c6c7,   
	0x4593e01e, 0x4152fda9, 0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,   
	0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3,   
	0x709f7b7a, 0x745e66cd, 0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039,   
	0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5, 0xbe2b5b58, 0xbaea46ef,   
	0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,   
	0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb,   
	0xceb42022, 0xca753d95, 0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,   
	0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d, 0x34867077, 0x30476dc0,   
	0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,   
	0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x018aeb13, 0x054bf6a4,   
	0x0808d07d, 0x0cc9cdca, 0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde,   
	0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02, 0x5e9f46bf, 0x5a5e5b08,   
	0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,   
	0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e, 0xbfa1b04b, 0xbb60adfc,   
	0xb6238b25, 0xb2e29692, 0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6,   
	0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a, 0xe0b41de7, 0xe4750050,   
	0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,   
	0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34,   
	0xdc3abded, 0xd8fba05a, 0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637,   
	0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb, 0x4f040d56, 0x4bc510e1,   
	0x46863638, 0x42472b8f, 0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,   
	0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5,   
	0x3f9b762c, 0x3b5a6b9b, 0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff,   
	0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623, 0xf12f560e, 0xf5ee4bb9,   
	0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,   
	0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd,   
	0xcda1f604, 0xc960ebb3, 0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,   
	0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b, 0x9b3660c6, 0x9ff77d71,   
	0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,   
	0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2,   
	0x470cdd2b, 0x43cdc09c, 0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8,   
	0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24, 0x119b4be9, 0x155a565e,   
	0x18197087, 0x1cd86d30, 0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,   
	0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088, 0x2497d08d, 0x2056cd3a,   
	0x2d15ebe3, 0x29d4f654, 0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0,   
	0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c, 0xe3a1cbc1, 0xe760d676,   
	0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,   
	0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662,   
	0x933eb0bb, 0x97ffad0c, 0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668,   
	0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
};

uint32_t CRC321(const uint8_t *data, int len)
{   
	int i;   
	uint32_t crc = 0xFFFFFFFF;       
	for(i = 0; i < len; i++) 
		crc = (crc << 8) ^ crc32table1[((crc >> 24) ^ *data++) & 0xFF];       
	return crc;
}
/***
 *@remark:  ����������ݰ���λһ��һ����ѹ������
 *@param :  buffer   [in]  ѹ�����ݵ�buffer
 *          count    [in]  ��Ҫѹ������ռ��λ��
 *          bits     [in]  ѹ�����ֵ
 */
#define bits_write(buffer, count, bits)\
{\
	bits_buffer_s *p_buffer = (buffer);\
	int i_count = (count);\
	uint64_t i_bits = (bits);\
	while( i_count > 0 )\
	{\
		i_count--;\
		if( ( i_bits >> i_count )&0x01 )\
		{\
			p_buffer->p_data[p_buffer->i_data] |= p_buffer->i_mask;\
		}\
		else\
		{\
			p_buffer->p_data[p_buffer->i_data] &= ~p_buffer->i_mask;\
		}\
		p_buffer->i_mask >>= 1;         /*������һ���ֽڵ�һλ�󣬲����ڶ�λ*/\
		if( p_buffer->i_mask == 0 )     /*ѭ����һ���ֽڵ�8λ�����¿�ʼ��һλ*/\
		{\
			p_buffer->i_data++;\
			p_buffer->i_mask = 0x80;\
		}\
	}\
}

/***
 *@remark:   rtpͷ�Ĵ������ѭ����������
 *@param :   pData      [in] ���͵����ݵ�ַ
 *           nDatalen   [in] �������ݵĳ���
 *           mark_flag  [in] mark��־λ
 *           curpts     [in] ʱ���
 *           pPacker    [in] ���ݰ��Ļ�����Ϣ
 *@return:   0 success, others failed
*/

int gb28181_send_rtp_pack(char *databuff, int nDataLen, int mark_flag, Data_Info_s* pPacker)
{
	int nRes = 0;
	int nPlayLoadLen = 0;
	int nSendSize    = 0;
	char szRtpHdr[RTP_HDR_LEN];
	memset(szRtpHdr, 0, RTP_HDR_LEN);
	
    if(nDataLen + RTP_HDR_LEN <= RTP_MAX_PACKET_BUFF)// 1460 pPackerָ�뱾����һ��1460��С��buffer���ݻ���
    {
        // һ֡���ݷ�����󣬸�mark��־λ��1
		gb28181_make_rtp_header(szRtpHdr, ((mark_flag == 1 )? 1 : 0 ), ++pPacker->u16CSeq, (pPacker->s64CurPts /300), pPacker->u32Ssrc);
		memcpy(pPacker->szBuff, szRtpHdr, RTP_HDR_LEN);
		memcpy(pPacker->szBuff + RTP_HDR_LEN, databuff, nDataLen);
        //nRet = SendDataBuff(databuff, RTP_HDR_LEN + nSendSize, pPacker);
		if (nRes != (RTP_HDR_LEN + nDataLen))
		{
			printf(" udp send error !\n");
			return -1;
		}
		
	}
	else 
	{
		nPlayLoadLen = RTP_MAX_PACKET_BUFF - RTP_HDR_LEN; // ÿ��ֻ�ܷ��͵����ݳ��� ��ȥrtpͷ
		gb28181_make_rtp_header(pPacker->szBuff, 0, ++pPacker->u16CSeq, (pPacker->s64CurPts/100), pPacker->u32Ssrc);
		memcpy(pPacker->szBuff + RTP_HDR_LEN, databuff, nPlayLoadLen);
        // nRet = SendDataBuff(databuff, RTP_HDR_LEN + nSendSize, pPacker);
		if (nRes != (RTP_HDR_LEN + nPlayLoadLen))
		{
			printf(" udp send error !\n");
			return -1;
		}
		
		nDataLen -= nPlayLoadLen;
		// databuff += (nPlayLoadLen - RTP_HDR_LEN);
		databuff += nPlayLoadLen; // ����ǰ�浽�����Ѿ����ͳ�ȥ 		
		databuff -= RTP_HDR_LEN; // �������rtpͷ
		while(nDataLen > 0)
		{
			if(nDataLen <= nPlayLoadLen)
			{
				//һ֡���ݷ����꣬��mark��־λ
				gb28181_make_rtp_header(databuff, mark_flag, ++pPacker->u16CSeq, (pPacker->s64CurPts/100), pPacker->u32Ssrc);
				nSendSize = nDataLen;
			}
			else 
			{
				gb28181_make_rtp_header(databuff, 0, ++pPacker->u16CSeq, (pPacker->s64CurPts/100), pPacker->u32Ssrc);
				nSendSize = nPlayLoadLen;
			}
            int nRet ;//= SendDataBuff(databuff, RTP_HDR_LEN + nSendSize, pPacker);
			if (nRes != (RTP_HDR_LEN + nSendSize))
			{
				printf(" udp send error !\n");
				return -1;
			}
			nDataLen -= nSendSize;
			databuff += nSendSize; 
			//��Ϊbufferָ���Ѿ�����ƶ�һ��rtpͷ���Ⱥ�
			//����ÿ��ѭ������rtp��ʱ��ֻҪ��ǰ�ƶ������ݵ����ȼ��ɣ�����bufferָ��ʵ��ָ��λ����
			//databuff����ظ���rtp���ȵ������ݵ�λ���� 

		}

	}
	return 0;
}

/***
 *@remark:   pesͷ�ķ�װ,����ľ������ݵ���д�Ѿ�ռλ�����Բο���׼
 *@param :   pData      [in] ���psͷ���ݵĵ�ַ
 *           stream_id  [in] ��������
 *           paylaod_len[in] ���س���
 *           pts        [in] ʱ���
 *           dts        [in]
 *@return:   0 success, others failed
*/
int gb28181_make_pes_header(char *pData, int stream_id, int payload_len, unsigned long long pts, unsigned long long dts)
{
	
	bits_buffer_s  	bitsBuffer;
	bitsBuffer.i_size = PES_HDR_LEN;
	bitsBuffer.i_data = 0;
	bitsBuffer.i_mask = 0x80;
	bitsBuffer.p_data =	(unsigned char *)(pData);
	memset(bitsBuffer.p_data, 0, PES_HDR_LEN);
	/*system header*/
	bits_write( &bitsBuffer, 24,0x000001);	/*start code*/
	bits_write( &bitsBuffer, 8, (stream_id));	/*streamID*/
	bits_write( &bitsBuffer, 16,(payload_len)+13);	/*packet_len*/ //ָ��pes���������ݳ��Ⱥ͸��ֽں�ĳ��Ⱥ�
	bits_write( &bitsBuffer, 2, 2 );		/*'10'*/
	bits_write( &bitsBuffer, 2, 0 );		/*scrambling_control*/
	bits_write( &bitsBuffer, 1, 0 );		/*priority*/
	bits_write( &bitsBuffer, 1, 0 );		/*data_alignment_indicator*/
	bits_write( &bitsBuffer, 1, 0 );		/*copyright*/
	bits_write( &bitsBuffer, 1, 0 );		/*original_or_copy*/
	bits_write( &bitsBuffer, 1, 1 );		/*PTS_flag*/
	bits_write( &bitsBuffer, 1, 1 );		/*DTS_flag*/
	bits_write( &bitsBuffer, 1, 0 );		/*ESCR_flag*/
	bits_write( &bitsBuffer, 1, 0 );		/*ES_rate_flag*/
	bits_write( &bitsBuffer, 1, 0 );		/*DSM_trick_mode_flag*/
	bits_write( &bitsBuffer, 1, 0 );		/*additional_copy_info_flag*/
	bits_write( &bitsBuffer, 1, 0 );		/*PES_CRC_flag*/
	bits_write( &bitsBuffer, 1, 0 );		/*PES_extension_flag*/
	bits_write( &bitsBuffer, 8, 10);		/*header_data_length*/ 
	// ָ�������� PES ��������еĿ�ѡ�ֶκ��κ�����ֽ���ռ�õ����ֽ��������ֶ�֮ǰ
	//���ֽ�ָ�������޿�ѡ�ֶΡ�
	
	/*PTS,DTS*/	
    bits_write( &bitsBuffer, 4, 3 );                    /*'0011'*/
    bits_write( &bitsBuffer, 3, ((pts)>>30)&0x07 );     /*PTS[32..30]*/
	bits_write( &bitsBuffer, 1, 1 );
    bits_write( &bitsBuffer, 15,((pts)>>15)&0x7FFF);    /*PTS[29..15]*/
	bits_write( &bitsBuffer, 1, 1 );
    bits_write( &bitsBuffer, 15,(pts)&0x7FFF);          /*PTS[14..0]*/
	bits_write( &bitsBuffer, 1, 1 );
    bits_write( &bitsBuffer, 4, 1 );                    /*'0001'*/
    bits_write( &bitsBuffer, 3, ((dts)>>30)&0x07 );     /*DTS[32..30]*/
	bits_write( &bitsBuffer, 1, 1 );
    bits_write( &bitsBuffer, 15,((dts)>>15)&0x7FFF);    /*DTS[29..15]*/
	bits_write( &bitsBuffer, 1, 1 );
    bits_write( &bitsBuffer, 15,(dts)&0x7FFF);          /*DTS[14..0]*/
	bits_write( &bitsBuffer, 1, 1 );
	return PES_HDR_LEN;
}

/***
 *@remark:   psmͷ�ķ�װ,����ľ������ݵ���д�Ѿ�ռλ�����Բο���׼
 *@param :   pData  [in] ���psͷ���ݵĵ�ַ
 *@return:   0 success, others failed
*/
int gb28181_make_psm_header(char *pData)
{
	
	bits_buffer_s  	bitsBuffer;
	bitsBuffer.i_size = PSM_HDR_LEN; 
	bitsBuffer.i_data = 0;
	bitsBuffer.i_mask = 0x80;
	bitsBuffer.p_data =	(unsigned char *)(pData);
	memset(bitsBuffer.p_data, 0, PSM_HDR_LEN);
	bits_write(&bitsBuffer, 24,0x000001);	/*start code*/
	bits_write(&bitsBuffer, 8, 0xBC);		/*map stream id*/
	bits_write(&bitsBuffer, 16,18);			/*program stream map length*/ 
	bits_write(&bitsBuffer, 1, 1);			/*current next indicator */
	bits_write(&bitsBuffer, 2, 3);			/*reserved*/
	bits_write(&bitsBuffer, 5, 0); 			/*program stream map version*/
    bits_write(&bitsBuffer, 7, 0x7F);		/*reserved */
	bits_write(&bitsBuffer, 1, 1);			/*marker bit */
	bits_write(&bitsBuffer, 16,0); 			/*programe stream info length*/
	bits_write(&bitsBuffer, 16, 8); 		/*elementary stream map length	is*/
	/*audio*/
    bits_write(&bitsBuffer, 8, 0x0f);       /*stream_type*/
    bits_write(&bitsBuffer, 8, 0xC0);		/*elementary_stream_id*/
	bits_write(&bitsBuffer, 16, 0); 		/*elementary_stream_info_length is*/
	/*video*/
    bits_write(&bitsBuffer, 8, 0x1B);       /*stream_type*/
    bits_write(&bitsBuffer, 8, 0xE0);		/*elementary_stream_id*/
	bits_write(&bitsBuffer, 16, 0); 		/*elementary_stream_info_length */
	/*crc (2e b9 0f 3d)*/
	uint32_t nCrc32 = CRC321((const uint8_t*)pData + 6,PSM_HDR_LEN - 10);

	bits_write(&bitsBuffer, 8, nCrc32>>24);
	bits_write(&bitsBuffer, 8, nCrc32>>16);
	bits_write(&bitsBuffer, 8, nCrc32>>8);
	bits_write(&bitsBuffer, 8, nCrc32);
	return PSM_HDR_LEN;
}

/***
 *@remark:   sysͷ�ķ�װ,����ľ������ݵ���д�Ѿ�ռλ�����Բο���׼
 *@param :   pData  [in] ���psͷ���ݵĵ�ַ
 *@return:   0 success, others failed
*/
int gb28181_make_sys_header(char *pData)
{
	
	bits_buffer_s  	bitsBuffer;
	bitsBuffer.i_size = SYS_HDR_LEN;
	bitsBuffer.i_data = 0;
	bitsBuffer.i_mask = 0x80;
	bitsBuffer.p_data =	(unsigned char *)(pData);
	memset(bitsBuffer.p_data, 0, SYS_HDR_LEN);
	/*system header*/
	bits_write( &bitsBuffer, 32, 0x000001BB);	/*start code*/
    bits_write( &bitsBuffer, 16, SYS_HDR_LEN-6);/*header_length ��ʾ���ֽں���ĳ��ȣ���������ͷҲ�Ǵ���˼*/
    bits_write( &bitsBuffer, 1,	 1);            /*marker_bit*/
	bits_write( &bitsBuffer, 22, 50000);		/*rate_bound*/
    bits_write( &bitsBuffer, 1,  1);            /*marker_bit*/
    bits_write( &bitsBuffer, 6,  1);            /*audio_bound*/
    bits_write( &bitsBuffer, 1,  0);            /*fixed_flag */
    bits_write( &bitsBuffer, 1,  1);        	/*CSPS_flag */
    bits_write( &bitsBuffer, 1,  1);        	/*system_audio_lock_flag*/
    bits_write( &bitsBuffer, 1,  1);        	/*system_video_lock_flag*/
    bits_write( &bitsBuffer, 1,  1);        	/*marker_bit*/
    bits_write( &bitsBuffer, 5,  1);        	/*video_bound*/
    bits_write( &bitsBuffer, 1,  0);        	/*dif from mpeg1*/
    bits_write( &bitsBuffer, 7,  0x7F);     	/*reserver*/
	/*audio stream bound*/
    bits_write( &bitsBuffer, 8,  0xC0);         /*stream_id*/
    bits_write( &bitsBuffer, 2,  3);        	/*marker_bit */
    bits_write( &bitsBuffer, 1,  0);            /*PSTD_buffer_bound_scale*/
    bits_write( &bitsBuffer, 13, 512);          /*PSTD_buffer_size_bound*/
	/*video stream bound*/
    bits_write( &bitsBuffer, 8,  0xE0);         /*stream_id*/
    bits_write( &bitsBuffer, 2,  3);        	/*marker_bit */
    bits_write( &bitsBuffer, 1,  1);        	/*PSTD_buffer_bound_scale*/
    bits_write( &bitsBuffer, 13, 2048);     	/*PSTD_buffer_size_bound*/
	return SYS_HDR_LEN;
}

/***
 *@remark:   psͷ�ķ�װ,����ľ������ݵ���д�Ѿ�ռλ�����Բο���׼
 *@param :   pData  [in] ���psͷ���ݵĵ�ַ
 *           s64Src [in] ʱ���
 *@return:   0 success, others failed
*/
int gb28181_make_ps_header(char *pData, unsigned long long s64Scr)
{
	unsigned long long lScrExt = (s64Scr) % 100;	
    s64Scr = s64Scr / 100;
    // �������100������sdpЭ�鷵�ص�video��Ƶ����90000��֡����25֡/s������ÿ�ε���������3600,
    // ����ʵ����Ӧ�ø������Լ��������ʱ����������Ա�֤ʱ���������Ϊ3600���ɣ�
    //������ﲻ�ԵĻ����Ϳ��ܵ��¿���������
	bits_buffer_s  	bitsBuffer;
	bitsBuffer.i_size = PS_HDR_LEN;	
	bitsBuffer.i_data = 0;
    bitsBuffer.i_mask = 0x80; // �����ƣ�10000000 ������Ϊ�˺����һ���ֽڵ�ÿһλ���в����������С�˿��ֽ��������
	bitsBuffer.p_data =	(unsigned char *)(pData);
	memset(bitsBuffer.p_data, 0, PS_HDR_LEN);
    bits_write(&bitsBuffer, 32, 0x000001BA);			/*start codes*/
	bits_write(&bitsBuffer, 2, 	1);						/*marker bits '01b'*/
    bits_write(&bitsBuffer, 3, 	(s64Scr>>30)&0x07);     /*System clock [32..30]*/
	bits_write(&bitsBuffer, 1, 	1);						/*marker bit*/
    bits_write(&bitsBuffer, 15, (s64Scr>>15)&0x7FFF);   /*System clock [29..15]*/
	bits_write(&bitsBuffer, 1, 	1);						/*marker bit*/
    bits_write(&bitsBuffer, 15, s64Scr&0x7fff);         /*System clock [29..15]*/
	bits_write(&bitsBuffer, 1, 	1);						/*marker bit*/
	bits_write(&bitsBuffer, 9, 	lScrExt&0x01ff);		/*System clock [14..0]*/
	bits_write(&bitsBuffer, 1, 	1);						/*marker bit*/
	bits_write(&bitsBuffer, 22, (255)&0x3fffff);		/*bit rate(n units of 50 bytes per second.)*/
	bits_write(&bitsBuffer, 2, 	3);						/*marker bits '11'*/
	bits_write(&bitsBuffer, 5, 	0x1f);					/*reserved(reserved for future use)*/
	bits_write(&bitsBuffer, 3, 	0);						/*stuffing length*/
	return PS_HDR_LEN;
}

/***
 *@remark:  ����Ƶ���ݵĴ����ps��������װ��rtp
 *@param :  pData      [in] ��Ҫ���͵�����Ƶ����
 *          nFrameLen  [in] �������ݵĳ���
 *          pPacker    [in] ���ݰ���һЩ��Ϣ������ʱ�����rtp����buff�����͵�socket�����Ϣ
 *          stream_type[in] �������� 0 ��Ƶ 1 ��Ƶ
 *@return:  0 success others failed
*/

int gb28181_streampackageForH264(char *pData, int nFrameLen, Data_Info_s* pPacker, int stream_type)
{
	char szTempPacketHead[256];
	int  nSizePos = 0;
	int  nSize = 0;		
	char *pBuff = NULL;
	memset(szTempPacketHead, 0, 256);
	// 1 package for ps header 
	gb28181_make_ps_header(szTempPacketHead + nSizePos, pPacker->s64CurPts);
	nSizePos += PS_HDR_LEN;	
	//2 system header 
	if( pPacker->IFrame == 1 )
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

    //����rtp���ͳ�ȥ�������Ļ�����������ݾ�ֻҪ��Ƭ�ְ���ֻ�м���pesͷ��rtpͷ��
	if(gb28181_send_rtp_pack(szTempPacketHead, nSizePos, 0, pPacker) != 0 )
		return -1;	

    // ��������ƶ���Ϊ�˷��㿽��pesͷ
    //������Ϊ�˼��ٺ�������Ƶ�����ݵĴ��������˷ѿռ䣬�������������ƶ�����ʵ�ʴ����ʱ��Ҫע���ַ�Ƿ�Խ���Լ����ǵ�����
	pBuff = pData - PES_HDR_LEN;
	while(nFrameLen > 0)
	{
        //ÿ��֡�ĳ��Ȳ�Ҫ����short���ͣ����˾͵÷�Ƭ��ѭ���з���
		nSize = (nFrameLen > 0xFFFF) ? 0xFFFF : nFrameLen;
        // ���pesͷ
		gb28181_make_pes_header(pBuff, stream_type ? 0xC0:0xE0, nSize, (pPacker->s64CurPts / 100), (pPacker->s64CurPts/300));

        //��������rtpͷ����������
		if( gb28181_send_rtp_pack(pBuff, nSize + PES_HDR_LEN, ((nSize == nFrameLen)?1:0), pPacker) != 0 )
		{
			printf("gb28181_send_pack failed!\n");
			return -1;
		}
        //��Ƭ��ÿ�η��͵������ƶ�ָ�����
		nFrameLen -= nSize;
        //����Ҳֻ�ƶ�nSize,��Ϊ��while����ƶ���pesͷ���ȣ������������pesͷ����
        pBuff     += nSize;
		
	}
	return 0;
}

int gb28181_make_rtp_header(char *pData, int marker_flag, unsigned short cseq, long long curpts, unsigned int ssrc)
{
	bits_buffer_s  	bitsBuffer;
	if (pData == NULL)
		return -1;
	bitsBuffer.i_size = RTP_HDR_LEN;
	bitsBuffer.i_data = 0;
	bitsBuffer.i_mask = 0x80;
	bitsBuffer.p_data =	(unsigned char *)(pData);
	memset(bitsBuffer.p_data, 0, RTP_HDR_LEN);
	bits_write(&bitsBuffer, 2, 0x02);	/* rtp version 	*/
	bits_write(&bitsBuffer, 1, 0);				/* rtp padding 	*/
	bits_write(&bitsBuffer, 1, 0);				/* rtp extension 	*/
	bits_write(&bitsBuffer, 4, 0);				/* rtp CSRC count */
	bits_write(&bitsBuffer, 1, (marker_flag));			/* rtp marker  	*/
	bits_write(&bitsBuffer, 7, 96);			/* rtp payload type*/
	bits_write(&bitsBuffer, 16, (cseq));			/* rtp sequence 	 */
	bits_write(&bitsBuffer, 32, (curpts)); 		/* rtp timestamp 	 */
	bits_write(&bitsBuffer, 32, (ssrc)); 		/* rtp SSRC	 	 */
	return 0;
}