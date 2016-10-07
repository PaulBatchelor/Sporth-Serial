#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>

int main()
{
    struct termios toptions;
    int fd;
    speed_t brate;

    const char *serialport = "/dev/ttyACM0";

    fd = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        fprintf(stderr, "Serial: unable to open port\n");
        return -1;
    }

    if (tcgetattr(fd, &toptions) < 0) {
        fprintf(stderr, "Serial: Couldn't get term attributes\n");
        return -1;
    }

    brate = B9600;

    cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);
    /* 8N1 */
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    /* no flow control */
    toptions.c_cflag &= ~CRTSCTS;

    /* turn on READ & ignore ctrl lines */
    toptions.c_cflag |= CREAD | CLOCAL;
    /* turn of s/w flow ctrl */
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY);

    /* make raw*/
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | IXANY);
    toptions.c_oflag &= ~OPOST;

    /* see: http://unixwiz.net/techtips/termios-vmin-vtime.html */
    toptions.c_cc[VMIN] = 0;
    toptions.c_cc[VTIME] = 20;

    if (tcsetattr(fd, TCSANOW, &toptions) < 0) {
        close(fd);
        fprintf(stderr, "Serial: Couldn't set term attributes\b");
        return -1;
    }

    unsigned char b = 0;
    ssize_t bytes;
    while(1) {
        bytes = read(fd, &b, 1);
        if(bytes > 0) {

        } else {

        }
        usleep(100);
    }
    return 0; 
}
