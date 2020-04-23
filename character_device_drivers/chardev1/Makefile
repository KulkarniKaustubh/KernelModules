obj-m += chardev.o

all:
	sudo make -C /lib/modules/5.3.0-42-generic/build M=/home/kaustubh/kernel_modules/character_device_drivers modules
	sudo insmod chardev.ko
	sudo mknod /dev/kaustubh c 238 0

clean:
	sudo make -C /lib/modules/5.3.0-42-generic/build M=/home/kaustubh/kernel_modules/character_device_drivers clean

remove:
	sudo rm /dev/kaustubh
	sudo rmmod chardev
