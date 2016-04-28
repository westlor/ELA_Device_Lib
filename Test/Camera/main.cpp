/*
 * main.cpp
 *
 *  Created on: 2016Äê3ÔÂ21ÈÕ
 *      Author: Westlor
 */
extern "C"{
#include <ela_fb.h>
}
#include <ela_camera.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <malloc.h>

Camera *camera;

void sign_func(int sign_num)
{
    switch(sign_num)
    {
        case SIGINT:
            printf("I have get SIGINT<Ctrl+c>, I'm going now..\n");
            camera->CloseDevice();
            exit(0);
            break;
    }
}

int main(void) {

    int width=640;
    int height=480;
    unsigned char* image;

    FB_Init();
    FB_Clear();
    camera=new Camera(width, height);
    if(!camera->OpenDevice()){
        printf("Cam Open error\n");
    	return -1;
    }

    image = (unsigned char*)malloc(width*height*32/8);
    printf("Waiting for signal SIGINT..\n");
    signal(SIGINT, sign_func);

    while(1){

    	if(!camera->GetBuffer(image)){
            break;
        }
        FB_Draw((char*)image, 80, 0, width, height);
    }

    return 0;
}


