#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>
#include<string.h>
#define MAX 64

// 400: systemcall pnametoid: (char* name)

// 401: systemcall pidtoname: (int pid, char* name, int len)

int main()
{
    // test systemcall pnametoid
    char name[MAX];
    puts("Enter process name to find: ");
    scanf("%s",name);
    long int status = syscall(400, name);
    printf("sys_pnametoid returned %ld\n", status);
    if (status == -1){
        printf("Status: Process name not found!\n");}
    else{
            printf("Status: success!\n");
            printf("Name = %s \n",name);    
            printf("PID =  %ld \n",status);
	}
    
    // test systemcall pidtoname
    int id = 0;
    puts("Enter process id to find: ");
    scanf("%d",&id);
    status = syscall(401, id, name, MAX);
    printf("sys_pidtoname returned %ld\n", status);
    if(status == -1)
    {
        printf("Status: Process id not found!\n");
    }
    else if ( status > 0) {
        printf("Status: Process id not found!\n");
    }
    else {
        printf("Status: Success!\n");
        printf("Process name: = %s\n", name);
        printf("PID =  %d \n", id);
    }

    return 0;
}