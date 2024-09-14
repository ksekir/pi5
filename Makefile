obj-m += gomel.o

gomel-objs := gomel_init.o gomel_fops.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	sudo insmod gomel.ko
	
	ls -l /dev/gomel
	ls -d /sys/class/gomel
	
	sudo rmmod gomel
	
	sudo dmesg -c	
	grep gomel /proc/devices

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
