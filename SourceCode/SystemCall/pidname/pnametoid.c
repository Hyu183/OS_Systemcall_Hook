#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/string.h>
#include <linux/printk.h>

#define MAX 64

asmlinkage long pnametoid(char* name){
    printk("pnametoid systemcall 400 \n");
    struct task_struct *task;
    char charname[MAX];
    copy_from_user(charname, name, MAX);
    printk("Process name: = %s \n",charname); 

    /* Bao ve task list */
    read_lock(&tasklist_lock);
    /* Duyet qua cac task */    
    for_each_process(task){
    
        if(strcmp(task->comm,charname) == 0){
            return task_pid_nr(task); 
        }
    }

    /* Go lock */
    read_unlock(&tasklist_lock);
    /* Khong tin tim thay */
    return -1;
}
