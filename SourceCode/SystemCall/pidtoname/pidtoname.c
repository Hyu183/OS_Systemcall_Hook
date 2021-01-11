#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/string.h>
#include <linux/slab.h>

#define MAX 64

asmlinkage long sys_pidtoname(int pid, char* buf, int len){
    printk("pidtoname syscall 401\n");
    struct task_struct *task;
    /* GFP_KERNEL - Cap phat ram normal kernel ram. May sleep. */
    char *process_name = kmalloc(MAX, GFP_KERNEL);

    /* Duyet qua cac task */
    for_each_process(task){
        if (task->pid == pid){
            strcpy(process_name, task->comm);
        
            if(strlen(task->comm) <= MAX)
            {
                process_name[strlen(task->comm)]= '\0';
            }
            printk("Process Name :=%s\n", process_name);
            copy_to_user(buf, process_name, len - 1);

            /* Neu len process_name lon hon len(buf) */
            if (strlen(process_name) > len - 1)
            {
                return strlen(process_name);
            }
            else return 0;
        }
    }
    /* Loi (Khong tim thay) */
    return -1;
}
