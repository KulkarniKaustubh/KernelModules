# obj-m += hello.o
# obj-m += hello_2.o
obj-m += hello_3.o

all:
	sudo make -C /lib/modules/5.3.0-42-generic/build M=/home/kaustubh/kernel_modules/hello_3 modules

clean:
	make -C /lib/modules/$(uname -r)/build M=$(pwd) clean
