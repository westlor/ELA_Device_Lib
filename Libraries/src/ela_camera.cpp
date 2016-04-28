/*
 * ela_camera.cpp
 *
 *  Created on: 2016年3月21日
 *      Author: Westlor
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>             /* getopt_long() */
#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h>          /* for videodev2.h */
#include <linux/videodev2.h>
#include "ela_camera.h"
#include "videodev2_samsung.h"

void Camera::DecodeYUV420SP(unsigned int* rgbBuf, unsigned char* yuv420sp, int width, int height) {
    int frameSize = width * height;
    int i = 0, y = 0;
    int uvp = 0, u = 0, v = 0;
    int y1192 = 0, r = 0, g = 0, b = 0;
    unsigned int xrgb8888;
    int xrgb8888Index = 0;

    for (int j = 0, yp = 0; j < height; j++) {
        uvp = frameSize + (j >> 1) * width;
        u = 0;
        v = 0;
        for (i = 0; i < width; i++, yp++) {
            y = (0xff & ((int) yuv420sp[yp])) - 16;
            if (y < 0) y = 0;
            if ((i & 1) == 0) {
                v = (0xff & yuv420sp[uvp++]) - 128;
                u = (0xff & yuv420sp[uvp++]) - 128;
            }

            y1192 = 1192 * y;
			r = (y1192 + 1634 * u);
			g = (y1192 - 833 * u - 400 * v);
			b = (y1192 + 2066 * v);

            if (r < 0) r = 0; else if (r > 262143) r = 262143;
            if (g < 0) g = 0; else if (g > 262143) g = 262143;
            if (b < 0) b = 0; else if (b > 262143) b = 262143;


            r = (unsigned char)(r >> 10);
            g = (unsigned char)(g >> 10);
            b = (unsigned char)(b >> 10);

            xrgb8888 = (unsigned int)((r << 16) | (g << 8) | b);
            rgbBuf[xrgb8888Index++] = xrgb8888;
        }
    }
}

Camera::Camera(int w, int h)
{
	char *DEV_NAME = (char*)"/dev/video0";
    memcpy(dev_name,DEV_NAME,strlen(DEV_NAME));
    io = IO_METHOD_MMAP;//IO_METHOD_READ;//IO_METHOD_MMAP;
    cap_image_size=0;
    width=w;
    height=h;
}

Camera::~Camera(){

}

unsigned int Camera::getImageSize(){
    return cap_image_size;
}

void Camera::CloseDevice() {
    stop_capturing();
    uninit_device();
    close_device();
}

void Camera::errno_exit(const char * s) {
    fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
    exit(EXIT_FAILURE);
}
int Camera::xioctl(int fd, int request, void * arg) {
    int r;
    do
        r = ioctl(fd, request, arg);
    while (-1 == r && EINTR == errno);
    return r;
}

int Camera::read_frame(unsigned char *image) {
    struct v4l2_buffer buf;

    //CLEAR (buf);
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf)) {
        switch (errno) {
        case EAGAIN:
            return 0;
        case EIO:
            /* Could ignore EIO, see spec. */
            /* fall through */
        default:
            errno_exit("VIDIOC_DQBUF");
        }
    }
    assert(buf.index < CAPTURE_BUFFER_NUMBER);

    DecodeYUV420SP((unsigned int*)image, (unsigned char*)buffers[0].start, width, height);

    if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
        errno_exit("VIDIOC_QBUF");

    return 1;
}
void Camera::stop_capturing(void) {
    enum v4l2_buf_type type;
    switch (io) {
    case IO_METHOD_READ:
        /* Nothing to do. */
        break;
    case IO_METHOD_MMAP:
    case IO_METHOD_USERPTR:
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (-1 == xioctl(fd, VIDIOC_STREAMOFF, &type))
            errno_exit("VIDIOC_STREAMOFF");
        break;
    }
}
bool Camera::start_capturing(void) {
    unsigned int i;
    enum v4l2_buf_type type;

    for (i = 0; i < CAPTURE_BUFFER_NUMBER; ++i) {
        struct v4l2_buffer buf;
        CLEAR (buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
            return false;
    }
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl(fd, VIDIOC_STREAMON, &type))
        return false;

    return true;
}
void Camera::uninit_device(void) {
    unsigned int i;
    switch (io) {
    case IO_METHOD_READ:
        free(buffers[0].start);
        break;
    case IO_METHOD_MMAP:
        for (i = 0; i < CAPTURE_BUFFER_NUMBER; ++i)
            if (-1 == munmap(buffers[i].start, buffers[i].length))
                errno_exit("munmap");
        break;
    case IO_METHOD_USERPTR:
        for (i = 0; i < CAPTURE_BUFFER_NUMBER; ++i)
            free(buffers[i].start);
        break;
    }
}

bool Camera::init_mmap(void) {

	bool CouldSetFrameRate = false;
	struct v4l2_streamparm StreamParam;
	memset(&StreamParam, 0, sizeof StreamParam);
	StreamParam.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (ioctl(fd, VIDIOC_G_PARM, &StreamParam) < 0)  {
		fprintf(stderr, "could not set frame rate\n");
	} else {
		CouldSetFrameRate = StreamParam.parm.capture.capability & V4L2_CAP_TIMEPERFRAME;
	}

	// map the capture buffer...
	struct v4l2_requestbuffers req;
    CLEAR (req);
    req.count = CAPTURE_BUFFER_NUMBER;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    if(ioctl(fd, VIDIOC_REQBUFS, &req) < 0) {

		fprintf(stderr, "request capture buffer failed\n");
		return false;
	}

	if (int(req.count) != CAPTURE_BUFFER_NUMBER) {

		fprintf(stderr, "capture buffer number is wrong\n");
		return false;
	}

    for (unsigned int i = 0; i < req.count; i++) {
        struct v4l2_buffer buf;
        CLEAR (buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        if (ioctl(fd, VIDIOC_QUERYBUF, &buf) < 0)
            errno_exit("VIDIOC_QUERYBUF");
        buffers[i].length = buf.length;
        buffers[i].start = mmap(NULL /* start anywhere */, buf.length,
                                        PROT_READ | PROT_WRITE /* required */,
                                        MAP_SHARED /* recommended */, fd, buf.m.offset);
        if (MAP_FAILED == buffers[i].start)
            return false;
    }

    struct v4l2_control ctrl;
	ctrl.id = V4L2_CID_CAMERA_CHECK_DATALINE;
	ctrl.value = 0;
	if(ioctl(fd, VIDIOC_S_CTRL,&ctrl)) {
		fprintf(stderr, "VIDIOC_S_CTRL V4L2_CID_CAMERA_CHECK_DATALINE failed\n");
		return false;
	}

    return true;
}

bool Camera::init_device(void) {

    v4l2_input input;
    memset(&input, 0, sizeof(struct v4l2_input));
    input.index = 0;
    if (ioctl(fd, VIDIOC_ENUMINPUT, &input) != 0) {

		fprintf(stderr, "No matching index found\n");
		return false;
	}
	if (!input.name) {

		fprintf(stderr, "No matching index found\n");
		return false;
	}
	if (ioctl(fd, VIDIOC_S_INPUT, &input) < 0) {

		fprintf(stderr, "VIDIOC_S_INPUT failed\n");
		return false;
	}

    struct v4l2_format fmt;
    CLEAR (fmt);
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = width;
    fmt.fmt.pix.height = height;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;
	fmt.fmt.pix.field = V4L2_FIELD_NONE;

    if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
        return false;
    if (-1 == xioctl(fd, VIDIOC_G_FMT, &fmt))
        return false;

    //原始摄像头数据每帧的大小
    cap_image_size = fmt.fmt.pix.sizeimage;
    init_mmap();

    return true;
}

void Camera::close_device(void) {
    if (-1 == close(fd))
        errno_exit("close");
    fd = -1;
}
bool Camera::open_device(void) {
    struct stat st;
    if (-1 == stat(dev_name, &st)) {
        fprintf(stderr, "Cannot identify '%s': %d, %s\n", dev_name, errno,
                strerror(errno));
        return false;
    }
    if (!S_ISCHR(st.st_mode)) {
        fprintf(stderr, "%s is no device\n", dev_name);
        return false;
    }
    fd = ::open(dev_name, O_RDWR | O_NONBLOCK);
    if (-1 == fd) {
        fprintf(stderr, "Cannot open '%s': %d, %s\n", dev_name, errno,
                strerror(errno));
        return false;
    }
    return true;
}

bool Camera::OpenDevice(){
    if (open_device()) {
        printf("Open video success\n");
        if (init_device()) {
            if (start_capturing())
                return true;
        }
    } else
        printf("open video failed\n");
    return false;
}

bool Camera::GetBuffer(unsigned char *image){

	fd_set fds;
    struct timeval tv;
    int r;

    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    /* Timeout. */
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    r = select(fd + 1, &fds, NULL, NULL, &tv);
    if (-1 == r) {
        errno_exit("select");
    }
    if (0 == r) {
        fprintf(stderr, "select timeout\n");
        exit(EXIT_FAILURE);
    }
    read_frame(image);

    return true;
}


