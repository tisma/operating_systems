obj-m := tester_1.o
obj-m += tester_2.o
obj-m += tester_3.o
obj-m += tester_4.o
obj-m += tester_5.o
obj-m += tester_6.o
obj-m += tester_7.o

KVERSION := $(shell uname -r)
KDIR := /lib/modules/$(KVERSION)/build
PWD := $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

rmall:
	rm -rf '*.o' '*.ko' *.mod.c '.tes*' Mod* mod* .tmp_versions/*

