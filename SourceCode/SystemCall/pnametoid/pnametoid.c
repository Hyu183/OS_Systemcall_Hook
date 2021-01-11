#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/string.h>

#define MAX 64

asmlinkage long sys_pnametoid(char* name){
    printk("pnametoid systemcall 400 \n");
    struct task_struct *task;
    char charname[MAX];
    copy_from_user(charname, name, MAX);
    printk("Process name: = %s \n",charname); 

    /* Duyet qua cac task */    
    for_each_process(task){
    
        if(strcmp(task->comm,charname) == 0){
            return (long)(task->pid); 
        }
    }
    /* Khong tin tim thay */
    return -1;
}
