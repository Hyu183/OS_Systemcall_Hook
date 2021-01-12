#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){

    int fd = open("open.txt", O_CREAT |O_WRONLY);

    if(write(fd, "DO AN THAT LA VUI...", 21) == 21) {
        printf("Done\n");
    }
    else{
        printf("Fail T_T\n");
    }

    return 0;
}