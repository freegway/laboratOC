#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

void mask(char *mas,short mode);
void func_proc(char *name);

int main(int argc, char *argv[])
{
        int i;
        if (argc == 1){
		argv[1]="./";
		argc++;
	}
        for (i=1; i<argc; i++){
                printf("%s:\n",argv[1]);
                func_proc(argv[i]);

        }
        return 0;
}
void func_proc(char *name)
{

        DIR *dir;
        struct dirent *entery;
        struct stat buf;
        const char *name1;
        char mas[10];
        if ((dir=opendir(name))==NULL){
                perror("opendir error");
                exit(0);}
        while ((entery=readdir(dir))!=NULL){
                name1=entery->d_name;
                if (stat(name1,&buf)==-1)
                        perror("stat error");

                else {
                        char *time = ctime(&buf.st_atime);
                        time[strlen(time)-1]=0;
                        mask(mas,buf.st_mode);
                        printf("%s %4u %-8s %-8s %8lld %s %s\n",mas, buf.st_nlink, getpwuid(buf.st_uid)->pw_name, getgrgid(buf.st_gid)->gr_name, buf.st_size, time,name1);

                }
        }
}

void mask(char *mas, short mode )
{
        strcpy(mas,"----------");
        if (S_ISDIR(mode))  mas[0]='d';
        if (mode & S_IRUSR) mas[1]='r';
        if (mode & S_IWUSR) mas[2]='w';
        if (mode & S_IXUSR) mas[3]='x';
        if (mode & S_IRGRP) mas[4]='r';
        if (mode & S_IWGRP) mas[5]='w';
        if (mode & S_IXGRP) mas[6]='x';
        if (mode & S_IROTH) mas[7]='r';
        if (mode & S_IWOTH) mas[8]='w';
        if (mode & S_IXOTH) mas[9]='x';
}


