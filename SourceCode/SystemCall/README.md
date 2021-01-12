# Ubuntu: 16.04.0

# Cai dat cac goi can thiet

sudo apt-get install gcc
sudo apt-get install libncurses5-dev
sudo apt-get install bison
sudo apt-get install flex
sudo apt-get install libssl-dev
sudo apt-get install libelf-dev
sudo apt-get update

# Download kernel 4.4.2 

wget https://mirrors.edge.kernel.org/pub/linux/kernel/v4.x/linux-4.4.2.tar.gz

## Giai nen vao thuc muc usr/src

sudo tar -xzvf linux-4.4.2.tar.gz –C /usr/src/

# Sua Make file trong linux-4.4.2

sudo gedit Makefile

Tim dong:
    core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/

Sua thanh:
    core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ pidtoname/ pnametoid/

## Tao thu muc pidname trong linux-4.4.2 (chua source code cho system call se dinh nghia)

sudo mkdir pidtoname pnametoid

touch pidtoname/ pidtoname.c Makefile (Copy source codde vao) hoac dung lenh cp, mv 

touch pnametoid/ pnametoid.c Makefile (Copy source codde vao) hoac dung lenh cp, mv 

# Dinh nghia ma cho systemcall moi

## Sua file syscall_32.tbl

cd /linux-4.4.2/arch/x86/entry/syscalls/
sudo gedit syscall_64.tbl

400	64	pnametoid			sys_pnametoid
401	64 	pidtoname			sys_pidtoname

# Dinh nghia ham trong systemcall header file (thêm vào trước #endif)

## Sua file syscalls.h (them vao cuoi truoc #endif)

cd /linux-4.4.2/include/linux
sudo gedit syscalls.h

asmlinkage long pnametoid(char* name);
asmlinkage long pidtoname(int pid, char* buf, int len);

# Bien dich kernel

make menuconfig (save config)

make -j4

make modules_install install

# Test 

make (trong folder test)

# Tham khao
https://github.com/nguyentathung943/Systemcall_and_Hook
