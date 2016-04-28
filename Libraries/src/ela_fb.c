/*
 * ela_fb.c
 *
 *  Created on: 2016Äê3ÔÂ9ÈÕ
 *      Author: Westlor
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ela_fb.h"
#include "ascii_8x16.h"

static FB_Dev screen;

int FB_Init() {
	if((screen.fd = open("/dev/fb0", O_RDWR)) == -1){
		printf("Error:Can not open /dev/fb0\n");
		return -1;
	}
	if(ioctl(screen.fd, FBIOGET_VSCREENINFO, &screen.vinfo) == -1){
		printf("Error:reading variable information\n");
		return -2;
	}
	if(ioctl(screen.fd, FBIOGET_FSCREENINFO, &screen.finfo) == -1){
		printf("Error:reading fixed information\n");
		return -3;
	}
	screen.screensize = screen.vinfo.xres * screen.vinfo.yres * screen.vinfo.bits_per_pixel/8;
	screen.fbp = (char *)mmap(0, screen.screensize, PROT_READ|PROT_WRITE,MAP_SHARED, screen.fd, 0);

	if((int) screen.fbp == -1){
		printf("Error:failed to map framebuffer device to memory.\n");
		return -4;
	}
	return 0;
}

void FB_Clear(){
	memset(screen.fbp, 0, screen.screensize);
}

void FB_Set(int color){
	int i , j ;
		for( i = 0 ; i < 800 ; i ++)
			for( j = 0 ; j < 480 ; j ++)
				FB_DrawPoint(i, j , color);
}

void FB_Draw(char* src, int x, int y, int w, int h){
	int i;
	int copyLen = w*(screen.vinfo.bits_per_pixel/8);
	int LineLen = screen.vinfo.xres * (screen.vinfo.bits_per_pixel/8);
	char *SrcPtr = src;
	char *DstPtr = screen.fbp + LineLen*y + x*(screen.vinfo.bits_per_pixel/8);

	for (i=0; i < h; i++) {
		memcpy(DstPtr, SrcPtr, copyLen);
		DstPtr += LineLen;
		SrcPtr += copyLen;
	}
}

void FB_DrawPoint(int x, int y, int color) {
	int fbp_offset = 0;
	if(x>=screen.vinfo.xres || y>=screen.vinfo.yres)
		return;
	fbp_offset = x * (screen.vinfo.bits_per_pixel/8) + y * screen.vinfo.xres * (screen.vinfo.bits_per_pixel/8);
	*(screen.fbp + fbp_offset) = color & 0xff;
	*(screen.fbp + fbp_offset + 1) = (color >> 8) & 0xff;
	*(screen.fbp + fbp_offset + 2) = (color >> 16) & 0xff;
	*(screen.fbp + fbp_offset + 3) = 0;
}

void FB_DrawVLine(int start_x, int start_y, int end_y, int color) {
    int tmp ;
    int i = 0;
    if(start_y > end_y)
    {
        start_y = start_y + end_y;
        end_y = start_y - end_y;
        start_y = start_y - end_y;
    }
    tmp = end_y - start_y;
    for( i = 0; i <= tmp ;  ++i)
    {
    	FB_DrawPoint(start_x, start_y + i, color);
    }
}

void FB_DrawHLine(int start_x, int start_y, int end_x, int color) {
    int tmp ;
    int i = 0;
    if(start_x > end_x)
    {
        start_x = start_x + end_x;
        end_x = start_x - end_x;
        start_x = start_x - end_x;
    }
    tmp = end_x - start_x;
    for( i = 0; i <= tmp ;  ++i)
    {
    	FB_DrawPoint(start_x + i, start_y, color);
    }
}

void FB_DrawRectangle(int start_x, int start_y, int end_x, int end_y, int color) {
	FB_DrawHLine(start_x, start_y , end_x ,color);
	FB_DrawHLine(start_x, end_y, end_x ,color);
	FB_DrawVLine(start_x, start_y , end_y ,color);
	FB_DrawVLine(end_x, start_y , end_y ,color);
}

void FB_DrawFullRectangle(int start_x, int start_y, int end_x, int end_y,
		int color) {
    int i = 0;
    int tmp = 0;
    tmp = end_x - start_x;
    for(i = 0; i < tmp; i ++)
    	FB_DrawVLine(start_x + i , start_y, end_y, color);
}

void FB_DrawWave(int start_x, int start_y, int t, int g, int color) {
    int i = 0, j = 0;
    int *screen_buffer = NULL;
    if((screen_buffer = (int *)malloc(screen.screensize)) == NULL)
    {
        printf("malloc error!\n");
    }
    memcpy(screen_buffer, screen.fbp, screen.screensize);
    while(1)
    {
        for(i = 0 ; i <= t/2; i ++ , start_x ++)
        {
            memcpy(screen.fbp, screen_buffer,screen.screensize);
            FB_DrawFullRectangle(start_x + 1,240, start_x + 10, 360, 0x0000);
            //memcpy(screen.fbp, screen_buffer,screen.screensize);
            FB_DrawPoint(start_x, start_y, color);
            memcpy(screen_buffer, screen.fbp, screen.screensize);
            sleep(0.001);
        }
        for(j =0; j <= g; j ++,start_y --)
        {
            memcpy(screen.fbp, screen_buffer,screen.screensize);
            FB_DrawFullRectangle(start_x + 1,240, start_x + 10, 360, 0x0000);
            //memcpy(screen.fbp, screen_buffer,screen.screensize);
            FB_DrawPoint(start_x, start_y, color);
            memcpy(screen_buffer, screen.fbp, screen.screensize);
            sleep(0.001);
        }
        for(i = 0; i <= t/2; i ++, start_x ++)
        {
            memcpy(screen.fbp, screen_buffer,screen.screensize);
            FB_DrawFullRectangle(start_x + 1,240, start_x + 10, 360, 0x0000);
            //memcpy(screen.fbp, screen_buffer,screen.screensize);
            FB_DrawPoint(start_x, start_y, color);
            memcpy(screen_buffer, screen.fbp, screen.screensize);
            sleep(0.001);
        }
        for(j = 0; j <= g; j ++ , start_y ++)
        {
            memcpy(screen.fbp, screen_buffer,screen.screensize);
            FB_DrawFullRectangle(start_x + 1,240, start_x + 10, 360, 0x0000);
            //memcpy(screen.fbp, screen_buffer,screen.screensize);
            FB_DrawPoint(start_x, start_y, color);
            memcpy(screen_buffer, screen.fbp, screen.screensize);
            sleep(0.001);
        }
		if(start_x >= 800)
			start_x = 0;
    }
}

void FB_DrawRectangleWave(int x0, int y0, int t, int g, int color) {
    int i;
    for(i = 0; i < 800; i += t)
    {
    	FB_DrawHLine(x0, x0 + t/2, y0,color);
    	FB_DrawVLine(x0 + t/2, y0 - g, y0, color);
        FB_DrawHLine(x0 + t/2,  x0 + t, y0 - g, color);
        FB_DrawVLine(x0 + t, y0 - g, y0, color);
        x0 = x0 + t;
    }
}

void FB_WriteEn(int x, int y, unsigned char* codes, int color) {
    int i = 0;
    for(i = 0; i < 16; ++ i)
    {
        int j = 0;
        x += 8;
        for(j = 0; j < 8; ++j)
        {
            --x;
            if((codes[i] >> j) & 0x1)
            {
                FB_DrawPoint(x , y, color);
            }
        }
        ++y;
    }
}

void FB_WriteCn(int x, int y, unsigned char* codes, int color) {
    int i;
    for( i = 0; i < 16; i ++)
    {
        int j = 0;
        for( j = 0; j < 2; j ++)
        {
            int k = 0;
            x += 8 * (j + 1);
            for( k = 0; k < 8; k ++)
            {
                -- x;
                if((codes[2 * i + j] >> k) & 0x1)
                    FB_DrawPoint(x, y, color);
            }
        }
    }
    x -= 8;
    ++ y;
}

void FB_WriteString(int x, int y, const char* str, int color) {
    unsigned char *ptr;
    unsigned int ch;
    unsigned int cl;
    unsigned int offset;
    while(*str)
    {
        ch = (unsigned int )str[0];
        cl = (unsigned int )str[1];
        if(( ch >= 0xa1) && (ch < 0xf8) && (cl >= 0xa1) && (cl < 0xff))
        {
            offset = ((ch - 0xa1) * 94 + (cl - 0xal)) * 32;
            ptr = __ASCII8X16__ + offset;
            FB_WriteCn(x, y, ptr,color);
            x += 16;
            str += 2;
        }
        else
        {
            ptr = __ASCII8X16__ + 16*ch;
            FB_WriteEn(x, y + 4, ptr, color);
            x += 8;
            str += 1;
        }
    }
}
