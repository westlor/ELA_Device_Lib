/*
 * ela_fb.h
 *
 *  Created on: 2016Äê3ÔÂ9ÈÕ
 *      Author: Westlor
 */

#ifndef LIBRARIES_ELA_FB_H_
#define LIBRARIES_ELA_FB_H_

#include <unistd.h>
#include <linux/types.h>
#include <linux/fb.h>
#include <sys/mman.h>

typedef struct{
	int fd;
    unsigned long screensize;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    char *fbp;
}FB_Dev;

int  FB_Init();
void FB_Clear();
void FB_Set(int color);
void FB_Draw(char* src, int x, int y, int w, int h);
void FB_DrawPoint(int x, int y, int color);
void FB_DrawVLine(int start_x, int start_y, int end_y, int color);
void FB_DrawHLine(int start_x, int start_y, int end_x, int color);
void FB_DrawRectangle(int start_x,int start_y, int end_x, int end_y , int color);
void FB_DrawFullRectangle(int start_x,int start_y, int end_x, int end_y , int color);
void FB_DrawWave(int start_x, int start_y, int t, int g, int color);
void FB_DrawRectangleWave(int x0, int y0, int t, int g, int color);
//void FB_WriteEn(int x, int y, unsigned char *codes, int color);
//void FB_WriteCn(int x, int y, unsigned char *codes, int color);
void FB_WriteString(int x, int y, const char * str,int color);

#endif /* LIBRARIES_ELA_FB_H_ */
