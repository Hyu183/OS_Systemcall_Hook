# Cai dat cac goi can thiet

sudo apt-get update
sudo apt-get upgrade
sudo apt-get install libncurses5-dev libncursesw5-dev
sudo apt-get install libssl-dev
sudo apt-get install libelf-dev
sudo apt-get install bison
sudo apt-get install flex
sudo apt-get install bc
sudo apt-get install perl

# Download kernel 3.13 

uname -r (Output: 3.13.0-24-generic)

wget https://mirrors.edge.kernel.org/pub/linux/kernel/v3.x/linux-3.13.tar.xz --no-check-certificate

## Giai nen vao thuc muc usr/src

sudo tar –xvf linux-3.13.tar.xz –C /usr/src/

# Sua Make file trong linux3.13

sudo gedit Makefile

Tim dong:
    core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/

Sua thanh:
    core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ pidname/

## Tao thu muc pidname trong linux-3.13 (chua source code cho system call se dinh nghia)

sudo mkdir pidname

# Dinh nghia ma cho systemcall moi

## Sua file syscall_32.tbl

cd /urs/src/linux-3.13/arch/x86/syscalls/
sudo gedit syscall_32.tbl

400	i386	pidname			pnametoid
401	i386	pidname			pidtoname

# Dinh nghia ham trong systemcall header file

## Sua file syscalls.h (them vao cuoi truoc #endif)

cd /usr/src/linux-3.13/include/linux
sudo gedit syscalls.h

asmlinkage int pnametoid(char* name);
asmlinkage int pidtoname(int pid, char* buf, int len);

# Source code

# Bien dich kernel

# Tham khao
https://github.com/nguyentathung943/Systemcall_and_Hook
