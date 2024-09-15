obj-m += gomel.o

gomel-objs := gomel_init.o gomel_proc_ops.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	sudo insmod gomel.ko
	
	# echo "Test message" > /proc/gomel
	# head -n1 /dev/gomel
	sudo rmmod gomel	
	sudo dmesg -c -T	

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
