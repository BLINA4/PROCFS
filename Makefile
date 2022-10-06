obj-m := procfs.o

all: procfs.c params.c
	gcc -x c -o PARAMS params.c
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	
5.10: procfs.c params.c
	gcc -x c -o PARAMS params.c
	sudo make -C /home/lnxd/4TB-2/Kernel/linux-5.10.8 M=$(PWD) modules
	
clean:
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
