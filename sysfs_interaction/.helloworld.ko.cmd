cmd_/home/kaustubh/kernel_modules/sysfs_interaction/helloworld.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000  --build-id  -T ./scripts/module-common.lds -o /home/kaustubh/kernel_modules/sysfs_interaction/helloworld.ko /home/kaustubh/kernel_modules/sysfs_interaction/helloworld.o /home/kaustubh/kernel_modules/sysfs_interaction/helloworld.mod.o;  true