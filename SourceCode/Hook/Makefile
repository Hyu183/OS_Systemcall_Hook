CONFIG_MODULE_SIG=n

obj-m += hook.o
  
KDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=`pwd` modules
	$(CC) test.c -o test
clean:
	make -C $(KDIR) M=`pwd` clean
	rm test