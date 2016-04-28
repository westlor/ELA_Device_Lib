/*
 ============================================================================
 Name        : LcdTest.c
 Author      : Westlor
 Version     :
 Copyright   : hwsys
 Description : ela_fb test in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ela_fb.h>
#include <color.h>

int main()
{
	FB_Init();
	FB_Set(WHITE);

	//----------------------------------------------------------

	FB_DrawFullRectangle(0, 0, 266, 150, 0x0037ae3);
	FB_WriteString(50, 40, "NIBP    120", WHITE);
	FB_WriteString(50, 60, "Alarm   ----  100 ", WHITE);
	FB_WriteString(50, 80, "         80       ", WHITE);

	FB_DrawFullRectangle(266, 0, 534, 150, GOLD);
	FB_WriteString(310, 40, "HR               BPM", RED);
	FB_WriteString(310, 60, "Alarm     78     ECG ", RED);
	FB_WriteString(310, 80, "Lead II           x1", RED);

	FB_DrawFullRectangle(534, 0, 800, 150, 0x00f30);
	FB_WriteString(545, 10, "SPO2 ", WHITE);
	FB_WriteString(550, 60, "Alarm           98 ", WHITE);
	FB_WriteString(640, 90, "Signal OK ", WHITE);

	FB_WriteString(0, 0, "Aanlyzing", GOLD);

	//---------------------------------------------------------

	FB_DrawFullRectangle(0, 150, 190, 300, 0x00f8000);
	FB_WriteString(50, 213, "Pacer Stop ", BLACK);
	FB_WriteString(45, 225, "Demand Mode ", BLACK);
	FB_WriteString(50, 237, "70ppm 30mA ", BLACK);

	FB_DrawFullRectangle(610,150,800,300,0x00ffff0);
	FB_WriteString(690, 213,"114J ",BLACK);
	FB_WriteString(680, 225,"Shock:0 ",BLACK);
	FB_WriteString(680, 237,"00:15:02 ",BLACK);

	//----------------------------------------------------------

	FB_DrawRectangle(190,260,380,300,BLUE);
	FB_WriteString(210,275,"Alarm    Temperature ",BLACK);

	FB_DrawRectangle(420,260,610,300,BLACK);
	FB_WriteString(430,275,"Alarm    Breach ",BLACK);

	//-----------------------------------------------------------

	FB_DrawVLine(190,436,479,0x00);
	FB_WriteString(210,442,"Stop ",0x00);

	FB_DrawVLine(265,436,479,0x00);
	FB_WriteString(285,442,"Alarm ",0x00);

	FB_DrawVLine(340,436,479,0x00);
	FB_WriteString(360,442,"Sign ",0x00);

	FB_DrawVLine(415,436,479,0x00);
	FB_DrawVLine(490,436,479,0x00);

	FB_WriteString(503,442,"Choouse ",0x00);
	FB_DrawVLine(565,436,479,0x00);
	FB_DrawVLine(640,436,479,0x00);

	FB_DrawHLine(190,436,640,0x00);

	return 0;
}
