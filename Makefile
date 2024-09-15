obj-m += gomel.o

gomel-objs := gomel_init.o gomel_fops.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	sudo insmod gomel.ko
	
	ls -l /dev/gomel
	ls -d /sys/class/gomel
	grep gomel /proc/devices
	sudo chmod 666 /dev/gomel
	echo "Test message" > /dev/gomel
	head -n1 /dev/gomel
	sudo rmmod gomel	
	sudo dmesg -c -T	

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
