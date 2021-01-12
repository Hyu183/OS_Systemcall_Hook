
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/highmem.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>
#include <linux/kallsyms.h>
#include <linux/slab.h>

#include <unistd.h>

#include <asm/unistd.h>
#include <asm/cacheflush.h>
#include <asm/pgtable_types.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("@18120168 @18120183");


/*MY sys_call_table address*/
//ffffffff81e00280
//grep -w sys_call_table /boot/System.map-$(uname -r)
void **SYS_CALL_TABLE = NULL;

asmlinkage int (*original_open)(const char *pathname, int flags, mode_t mode);
asmlinkage ssize_t (*original_write)(int fd, const void *buf, size_t count);

/*hook*/
asmlinkage int hookOpen(const char *pathname, int flags, mode_t mode) {
    char *buf = (char*)kmalloc(255, GFP_KERNEL);
    copy_from_user(buf,pathname,255);

    printk(KERN_INFO"[Hook Open] Process name open file: \"%s\" | Filename: %s\n",current->comm,buf);
    kfree(buf);

    return original_open(pathname,flags,mode);
}

asmlinkage ssize_t hookWrite(int fd, const void *buf, size_t count){
    char *proclink = (char*)kmalloc(1024,GFP_KERNEL);
    char *filename = (char*)kmalloc(255, GFP_KERNEL);
    ssize_t r =0;

    sprintf(proclink, "/proc/self/fd/%d", fd);
    r = readlink(proclink, filename, 1024);
    filename[r] = '\0';


    printk(KERN_INFO"[Hook Write] Process name write file: \"%s\" | Filename: %s | Write %zu bytes\n",current->comm,filename,count);
    kfree(proclink);
    kfree(filename);

    return original_write(fd,buf,count);
}


/*Make page writeable*/
int make_rw(unsigned long address){
    unsigned int level;
    pte_t *pte = lookup_address(address, &level);

    if(pte->pte &~_PAGE_RW){
        pte->pte |=_PAGE_RW;
    }

    return 0;
}


/* Make the page write protected */
int make_ro(unsigned long address){
    unsigned int level;
    pte_t *pte = lookup_address(address, &level);

    pte->pte = pte->pte &~_PAGE_RW;

    return 0;
}


//Init

static int __init init_Hook(void){
    printk(KERN_INFO "Hook loaded successfully..\n");

    /*MY sys_call_table address*/
    //printk("The address of sys_call_table is: %lx\n", kallsyms_lookup_name("sys_call_table"));
    SYS_CALL_TABLE = (void*)0xffffffff81e00280;

    /* Replace custom syscall with the correct system call name (write,open,etc) to hook*/
    original_open = SYS_CALL_TABLE[__NR_open];
    original_write = SYS_CALL_TABLE[__NR_write];

    /*Disable page protection*/
    make_rw((unsigned long)SYS_CALL_TABLE);

    /*Change syscall to our syscall function*/
    SYS_CALL_TABLE[__NR_open] = hookOpen;
    SYS_CALL_TABLE[__NR_write] = hookWrite;

    return 0;
}


static int __exit exit_Hook(void){
    printk(KERN_INFO "Unloaded Hook successfully\n");

    /*Restore original system call */
    SYS_CALL_TABLE[__NR_open] = original_open;
    SYS_CALL_TABLE[__NR_write] = original_write;

    /*Renable page protection*/
    make_ro((unsigned long)SYS_CALL_TABLE);

    return 0;
}


module_init(init_Hook);
module_exit(exit_Hook);