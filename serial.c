#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <soundpipe.h>
#include <sporth.h>

#define SERIALPORT "/dev/ttyACM0"

#if defined(TEST1) || defined(TEST2) || defined(TEST3)
#define BAUDRATE B9600
#else 
#define BAUDRATE B115200
#endif

//#define BAUDRATE B115200

#if defined(TEST4)
#define USE_PUSHBUTTON
#endif

typedef struct {
    struct termios toptions;
    int fd;
    speed_t brate;
    unsigned char b[4];
} serial_d;


static int serial_data_init(serial_d *sd, const char *portname)
{
    sd->fd = open(portname, O_RDWR | O_NOCTTY | O_NDELAY);
    if (sd->fd == -1) {
        fprintf(stderr, "Serial: unable to open port\n");
        return -1;
    }

    if (tcgetattr(sd->fd, &sd->toptions) < 0) {
        fprintf(stderr, "Serial: Couldn't get term attributes\n");
        return -1;
    }

    sd->brate = BAUDRATE;

    cfsetispeed(&sd->toptions, sd->brate);
    cfsetospeed(&sd->toptions, sd->brate);
    /* 8N1 */
    sd->toptions.c_cflag &= ~PARENB;
    sd->toptions.c_cflag &= ~CSTOPB;
    sd->toptions.c_cflag &= ~CSIZE;
    sd->toptions.c_cflag |= CS8;
    /* no flow control */
    sd->toptions.c_cflag &= ~CRTSCTS;

    /* turn on READ & ignore ctrl lines */
    sd->toptions.c_cflag |= CREAD | CLOCAL;
    /* turn of s/w flow ctrl */
    sd->toptions.c_iflag &= ~(IXON | IXOFF | IXANY);

    /* make raw*/
    sd->toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | IXANY);
    sd->toptions.c_oflag &= ~OPOST;

    /* see: http://unixwiz.net/techtips/termios-vmin-vtime.html */
    sd->toptions.c_cc[VMIN] = 0;
    sd->toptions.c_cc[VTIME] = 20;

    sd->b[0] = 0;
    sd->b[1] = 0;
    sd->b[2] = 0;
    sd->b[3] = 0;

    if (tcsetattr(sd->fd, TCSANOW, &sd->toptions) < 0) {
        close(sd->fd);
        fprintf(stderr, "Serial: Couldn't set term attributes\b");
        return -1;
    }

    return 0;
}

#ifdef STANDALONE

int main()
{
    serial_d sd;

    if(serial_data_init(&sd, SERIALPORT)) {
        return -1;
    }

    unsigned char b[4];
    ssize_t bytes;
    while(1) {
        bytes = read(sd.fd, b, 4);
        if(bytes >= 4 && b[0] == 255) {
            printf("%d %d %d %d\n", 
                b[0], b[1], b[2], b[3]);
        } else {

        }
        usleep(100);
    }
    return 0; 
}

#endif

int sporth_serial(plumber_data *pd, sporth_stack *stack, void **ud)
{
    unsigned char b = 0;
    ssize_t bytes;
    serial_d *sd;
    switch(pd->mode) {
        case PLUMBER_CREATE: 
            sd = malloc(sizeof(serial_d));
            if(serial_data_init(sd, SERIALPORT)) {
                return PLUMBER_NOTOK;
            }
            *ud = sd;
            sporth_stack_push_float(stack, 0);
            break;
        case PLUMBER_INIT: 
            sporth_stack_push_float(stack, 0);
            break;
        case PLUMBER_COMPUTE: 
            sd = *ud;
            bytes = read(sd->fd, &b, 1);
            if(bytes > 0) {
                sporth_stack_push_float(stack, (SPFLOAT) b);
            } else {
                sporth_stack_push_float(stack, -1);
            }
            break;
        case PLUMBER_DESTROY: 
            sd = *ud;
            free(sd); 
            break;
    }

    return PLUMBER_OK;
}

int sporth_serial2(plumber_data *pd, sporth_stack *stack, void **ud)
{
    unsigned char b[3];
    ssize_t bytes;
    serial_d *sd;
    switch(pd->mode) {
        case PLUMBER_CREATE: 
            sd = malloc(sizeof(serial_d));
            if(serial_data_init(sd, SERIALPORT)) {
                return PLUMBER_NOTOK;
            }
            *ud = sd;
            sporth_stack_push_float(stack, 0);
            sporth_stack_push_float(stack, 0);
#ifdef USE_PUSHBUTTON
            sporth_stack_push_float(stack, 0);
#endif
            break;
        case PLUMBER_INIT: 
            sporth_stack_push_float(stack, 0);
            sporth_stack_push_float(stack, 0);
#ifdef USE_PUSHBUTTON
            sporth_stack_push_float(stack, 0);
#endif
            break;
        case PLUMBER_COMPUTE: 
            sd = *ud;
#ifdef USE_PUSHBUTTON
            bytes = read(sd->fd, b, 4);
            if(b[0] == 255 && bytes >= 4) 
#else
            bytes = read(sd->fd, b, 3);
            if(b[0] == 255 && bytes >= 3) 
#endif
            {
                sd->b[1] = b[1];
                sd->b[2] = b[2];
#ifdef USE_PUSHBUTTON
                sd->b[3] = b[3];
#endif
            } 
            sporth_stack_push_float(stack, (SPFLOAT) sd->b[1]);
            sporth_stack_push_float(stack, (SPFLOAT) sd->b[2]);
#ifdef USE_PUSHBUTTON
            sporth_stack_push_float(stack, (SPFLOAT) sd->b[3]);
#endif
            break;
        case PLUMBER_DESTROY: 
            sd = *ud;
            free(sd); 
            break;
    }

    return PLUMBER_OK;
}

plumber_dyn_func sporth_return_ugen()
{
#if defined(TEST1)
    return sporth_serial;
#else
    return sporth_serial2;
#endif
}
