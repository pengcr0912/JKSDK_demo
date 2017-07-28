/******************************************************************************

  Copyright (C), 2007-2017, Hisilicon Tech. Co., Ltd.
  ******************************************************************************
  File Name     : hi_h264sample.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia
  Created       : 2007/05/17
  Description   :
  History       :
  1.Date        : 2007/07/07
  Author        : y39262
  Modification  : Created file
******************************************************************************/
#include "hi_config.h"
#include "hi_h264api.h"



#define BYTE_LEN 0x8000


int main(HI_S32 argc,HI_U8** argv)
{
    HI_S32 end = 0, input_param;
    HI_U8  buf[BYTE_LEN];
    H264_DEC_ATTR_S   dec_attrbute;
    H264_DEC_FRAME_S  dec_frame;
    H264_LIBINFO_S    lib_info;
	H264_USERDATA_S   hi3511_waterkark_key;
    HI_HDL handle = NULL;
    LARGE_INTEGER lpFrequency;
    LARGE_INTEGER t1;
    LARGE_INTEGER t2;
    HI_U32 time;
    HI_U32 pic_cnt = 0;
    HI_U32 ImageEnhanceEnable = 0;
	HI_U32 MultiThreadEnable = 0;
    HI_U32 StrenthCoeff = 40;
    HI_S32 WatermarkEnable = 0;
    HI_S32 DeinterlaceEnable = 0;
    HI_S32 DirectOutputEnable = 0;
	HI_S32 ShowFrameInfo = 0;
	HI_S32 CropEnable = 0;
    FILE *h264 = NULL;          //input h264 stream file
    FILE *yuv = NULL;           //file to save yuv
	HI_U32 tmpW = 0;
	HI_U32 tmpH = 0;

    if ( 0 == Hi264DecGetInfo(&lib_info) )
    {
        fprintf(stderr, "Version: %s\nCopyright: %s\n\n", lib_info.sVersion, lib_info.sCopyRight);
		fprintf(stderr, "FunctionSet: 0x%x\n", lib_info.uFunctionSet);
    }

    if (argc < 2)
    {
        fprintf(stderr, "Comand format or no H.264 stream! The Example:\n");
        fprintf(stderr, "hi_h264dec_w.exe stream_file.264 [-o yuvfile] [-direct] [-gamma] [-multithread] [-crop] [-showinfo] [-deinterlace]\n\n");
        goto exitmain;
    }

	/* open input bitstream file(necessary) */
	h264 = fopen(argv[1], "rb");
    if (NULL == h264)
    {
        fprintf(stderr, "Unable to open a h264 stream file %s \n", argv[1]);
        goto exitmain;
    }
    printf("decoding file: %s...\n",argv[1]);

	/* parse optional parameters */
	for(input_param = 2; input_param<argc; input_param++)
	{
		if(strcmp("-gamma", argv[input_param]) == 0)
		{
			ImageEnhanceEnable = 1;
			continue;
		}
		else if (strcmp("-deinterlace", argv[input_param]) == 0)
		{
			DeinterlaceEnable = 1;
			continue;
		}
		else if(strcmp("-wm", argv[input_param]) == 0 && (input_param+1)<argc)
		{
			WatermarkEnable = 1;
            /*init hi3511 watermark key */
        	hi3511_waterkark_key.uUserDataType = 0;
			hi3511_waterkark_key.uUserDataSize = 8;
			hi3511_waterkark_key.pData = argv[++input_param];
			hi3511_waterkark_key.pNext = NULL;
			continue;
		}
		else if(strcmp("-multithread", argv[input_param]) == 0)
		{
			MultiThreadEnable = 1;
			continue;
		}
		else if(strcmp("-crop", argv[input_param]) == 0)
		{
			CropEnable = 1;
			continue;
		}
		else if(strcmp("-direct", argv[input_param]) == 0)
		{
			DirectOutputEnable = 1;
			continue;
		}
		else if(strcmp("-showinfo", argv[input_param]) == 0)
		{
			ShowFrameInfo = 1;
			continue;
		}
		else if(strcmp("-o", argv[input_param]) == 0 && (input_param+1)<argc)
		{
            /* open yuv file */
            yuv = fopen(argv[++input_param], "wb");
            if (NULL == yuv)
            {
                fprintf(stderr, "Unable to open the file to save yuv %s.\n", argv[input_param]);
                goto exitmain;
            }
            printf("save yuv file: %s...\n",argv[input_param]);
		}
	}

    /*init the config info for docoder*/
    dec_attrbute.uBufNum        = 16;     // reference frames number: 16
    dec_attrbute.uPicHeightInMB = 70;     // D1(720x576)
    dec_attrbute.uPicWidthInMB  = 128;
    dec_attrbute.uStreamInType  = 0x00;   // bitstream begin with "00 00 01" or "00 00 00 01"

	if(DirectOutputEnable)
	{
		/* bit0 = 1: H.264 normal output mode; bit0 = 0: direct output mode */
		dec_attrbute.uWorkMode = 0x00;
	}
	else
	{
		dec_attrbute.uWorkMode = 0x01;
	}

    if(DeinterlaceEnable)
	{
		/* bit4 = 1:  enable deinteralce;    bit4 = 0: disable deinterlace */
		dec_attrbute.uWorkMode |= 0x10;
	}

	// ¶àÏß³Ì
	if (MultiThreadEnable)
	{
	    dec_attrbute.uWorkMode |= 0x20;
	}

	if(WatermarkEnable)
	{
        dec_attrbute.pUserData  = &hi3511_waterkark_key; 
		dec_attrbute.uWorkMode |= 0x02;
        //printf("ImageEnhanceEnable\n");
	}
	else 
	{
        dec_attrbute.pUserData  = NULL;   // no user data
	}



    /*create a decoder*/
    handle = Hi264DecCreate(&dec_attrbute);
    if(NULL ==  handle)
    {
        goto exitmain;
    }

    /* count decoding time: start */
    QueryPerformanceFrequency(&lpFrequency);
    QueryPerformanceCounter(&t1);

    /* dec the h264 stream file */
    while (!end)
    {
        /* read bitstream from "h264" */
        HI_U32  len = (HI_U32)fread(buf,1,sizeof(buf),h264);
        HI_U32  flags = (len>0)?0:1;
        HI_S32 result = 0;

        result = Hi264DecFrame(handle, buf,  len, 0, &dec_frame,  flags);

        while(HI_H264DEC_NEED_MORE_BITS  !=  result)
        {
            if(HI_H264DEC_NO_PICTURE ==  result)   //flush over and all the remain picture are output
            {
                end = 1;
                break;
            }

            if(HI_H264DEC_OK == result)   //get a picture
            {
                if (ImageEnhanceEnable)    //image enhance
                {
                    Hi264DecImageEnhance(handle, &dec_frame, StrenthCoeff);
                }
                
                if (ShowFrameInfo)
				{
					printf("PicBytes: %8d, I4:%4d,I8:%4d,I16:%4d, Pskip:%4d,P16:%4d,P16x8:%4d,P8x16:%4d,P8:%4d\n", 
						dec_frame.pFrameInfo->uPicBytes,
						dec_frame.pFrameInfo->uI4MbNum,
						dec_frame.pFrameInfo->uI8MbNum,
						dec_frame.pFrameInfo->uI16MbNum,
						dec_frame.pFrameInfo->uPskipMbNum,
						dec_frame.pFrameInfo->uP16MbNum,
						dec_frame.pFrameInfo->uP16x8MbNum,
						dec_frame.pFrameInfo->uP8x16MbNum,
						dec_frame.pFrameInfo->uP8MbNum);
				}

				/* get & print user data */
                if (NULL != dec_frame.pUserData && WatermarkEnable)
                {
                    HI_U32 i;
                    printf("frame:%d , user data type: %d;  user data length: %d\n",pic_cnt,
                        dec_frame.pUserData->uUserDataType,
                        dec_frame.pUserData->uUserDataSize);
                    for(i=0; i<dec_frame.pUserData->uUserDataSize; i++)
                        printf("%c",dec_frame.pUserData->pData[i]);
                    printf("\n");
                
				    if (NULL != dec_frame.pUserData->pNext)
                    {
                      HI_U32 i;
                      printf("frame:%d , user data type: %d;  user data length: %d\n",pic_cnt,
					 	dec_frame.pUserData->pNext->uUserDataType,
						dec_frame.pUserData->pNext->uUserDataSize);
					  for(i=0; i<dec_frame.pUserData->pNext->uUserDataSize; i++)
						printf("%c",dec_frame.pUserData->pNext->pData[i]);
                      printf("\n");
                    }
			    }

				if (CropEnable)
				{
					printf("CropInfo: top: %d, bot: %d, left: %d, right: %d.\n", 
						dec_frame.uCroppingTopOffset, dec_frame.uCroppingBottomOffset,
						dec_frame.uCroppingLeftOffset, dec_frame.uCroppingRightOffset);
				}

                if(NULL !=  yuv )
                {
                    const HI_U8 *pY = dec_frame.pY;
                    const HI_U8 *pU = dec_frame.pU;
                    const HI_U8 *pV = dec_frame.pV;
                    HI_U32 width    = dec_frame.uWidth;
                    HI_U32 height   = dec_frame.uHeight - dec_frame.uCroppingBottomOffset;
                    HI_U32 yStride  = dec_frame.uYStride;
                    HI_U32 uvStride = dec_frame.uUVStride;

                    fwrite(pY, 1, height* yStride, yuv);
                    fwrite(pU, 1, height* uvStride/2, yuv);
                    fwrite(pV, 1, height* uvStride/2, yuv);
                }

				if (tmpW != dec_frame.uWidth || tmpH != dec_frame.uHeight)
				{
					printf("Size change-->width: %d, height: %d, stride: %d\n", dec_frame.uWidth, dec_frame.uHeight, dec_frame.uYStride);
					tmpW = dec_frame.uWidth;
					tmpH = dec_frame.uHeight;
				}
                pic_cnt++;

               
            }
            /* continue decoding the remaining bitstream */
            result = Hi264DecFrame(handle, NULL,  0, 0, &dec_frame,  flags);
        }
    }

    /* count decoding time: end */
    QueryPerformanceCounter(&t2);
    time = (HI_U32)((t2.QuadPart-t1.QuadPart)*1000/lpFrequency.QuadPart);
    printf("\ntime= %d ms\n", time);
    printf("%d frames\n",pic_cnt);
    printf("fps: %d\n", pic_cnt*1000/(time+1));

    /* destory decoder */
    Hi264DecDestroy(handle);

exitmain:

    if (NULL != h264)
    {
        fclose(h264);
    }

    if (NULL != yuv)
    {
        fclose(yuv);
    }

    return 0;
}


