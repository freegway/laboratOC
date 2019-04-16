#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

/*int fd_set_blocking(int fd, int blocking)
{
        int flags = fcntl(fd, F_GETFL, 0);
        if (flags == -1)
                return 0;
        if (blocking)
                flags &= ~O_NONBLOCK;
        else flags |= O_NONBLOCK;
        return fcntl(fd, F_SETFL, flags) != -1;
}*/

int main(int argc, char *argv[])
{
        printf ("%d \n", argc);
        printf ("%s %s \n", argv[1], argv[2]);
        if (argc!=3){
                perror("error");
                return 0;
        }
        int fd1, fd2;

        if ((fd1=open(argv[1], O_RDONLY, 0)==-1)){
                perror("error");
                return 0;
        }
        if ((fd2=creat(argv[2], 0666)==-1)){
                perror("error");
                return 0;
        }
        int count=1;
        char buf[BUFSIZ];
        /*if ((fd_set_blocking(fd1, 0))==0){
                perror("error");
                return 0;
        }*/

        count = read(fd1, buf, BUFSIZ);
        printf ("%d ", count);

        /*while (count!=0)
        {
                printf ("%d ", count);
                count = read(fd1, buffer, BUFSIZ);
		printf ("%d ", count);
                if (count < 0 && errno == EAGAIN)
                {
                        return 0;
                }
                else if (count >= 0){
                        if ((write(fd2, buffer, count))==-1)
                                perror("error");
                        printf ("%d\n", count);
                        return 0;
                }
                else {
                        perror("error");
                }
        }*/

        return 0;
}

