# Ubuntu: 16.04.0

Phiên bản của kernel của ubuntu là 4.4.0-21-generic

# Cài đặt các gói cần thiết

sudo apt-get install gcc
sudo apt-get install libncurses5-dev
sudo apt-get install bison
sudo apt-get install flex
sudo apt-get install libssl-dev
sudo apt-get install libelf-dev
sudo apt-get update

# Download kernel 4.4.2 

wget https://mirrors.edge.kernel.org/pub/linux/kernel/v4.x/linux-4.4.2.tar.gz

## Giải nén vào thư mục usr/src

sudo tar -xzvf linux-4.4.2.tar.gz –C /usr/src/

# Sửa Make file trong linux-4.4.2

sudo gedit Makefile

Tìm dòng:
    core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/

Sửa thành:
    core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ pidtoname/ pnametoid/

## Tạo thư mục pidtoname và pnametoid trong linux-4.4.2 (Nơi chứa định nghĩa của systemcall)

sudo mkdir pidtoname pnametoid

sudo touch pidtoname/ pidtoname.c Makefile (Copy source codde vào) hoặc dùng lệnh sudo cp, mv 

sudo touch pnametoid/ pnametoid.c Makefile (Copy source codde vào) hoặc dùng lệnh sudo cp, mv 

# Định nghĩa mã cho hàm systemcall

## Sửa file syscall_32.tbl

cd /linux-4.4.2/arch/x86/entry/syscalls/
sudo gedit syscall_64.tbl

400	64	pnametoid			sys_pnametoid
401	64 	pidtoname			sys_pidtoname

# Định nghĩa hàm syscall trong header file

## Sửa file syscalls.h (thêm vào cuối trước #endif)

cd /linux-4.4.2/include/linux
sudo gedit syscalls.h

asmlinkage long pnametoid(char* name);
asmlinkage long pidtoname(int pid, char* buf, int len);

# Biên dịch kernel

make menuconfig (save config)

make -j4

make modules_install install

# Test 

make (trong folder test)

# Tham khảo
https://github.com/nguyentathung943/Systemcall_and_Hook
