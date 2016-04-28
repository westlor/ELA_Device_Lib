/*
 * ela_camera.h
 *
 *  Created on: 2016Äê3ÔÂ21ÈÕ
 *      Author: Westlor
 */

#ifndef LIBRARIES_INC_ELA_CAMERA_H_
#define LIBRARIES_INC_ELA_CAMERA_H_

#include <sys/types.h>

#define CLEAR(x) memset (&(x), 0, sizeof (x))
#define CAPTURE_BUFFER_NUMBER	1
typedef enum {
    IO_METHOD_READ, IO_METHOD_MMAP, IO_METHOD_USERPTR,
} io_method;

class Camera
{
public:
    Camera(int w,int h);
    ~Camera();
    bool OpenDevice();
    void CloseDevice();
    bool GetBuffer(unsigned char *image);
    unsigned int getImageSize();
    void DecodeYUV420SP(unsigned int* rgbBuf, unsigned char* yuv420sp, int width, int height);

private:
    char dev_name[50];
    io_method io;
    int fd;
    int width;
    int height;
    struct { void * start; int length; } buffers[CAPTURE_BUFFER_NUMBER];
    unsigned int cap_image_size ;

    bool init_device(void);
    bool init_mmap(void);
    void uninit_device(void);
    bool start_capturing(void);
    void stop_capturing(void);
    void mainloop(unsigned char *image);
    int read_frame(unsigned char *image);
    void close_device(void);
    bool open_device(void);
    bool process_image(unsigned char *image,const void * p);

    void errno_exit(const char * s);
    int xioctl(int fd, int request, void * arg);
};

#endif /* LIBRARIES_INC_ELA_CAMERA_H_ */
