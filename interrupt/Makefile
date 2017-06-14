ifneq ($(KERNELRELEASE),)

obj-m += __tasklet_hi_schedule.o __tasklet_schedule.o \
	disable_irq_nosync.o

else
PWD := $(shell pwd)

KVER := $(shell uname -r)
KDIR := /lib/modules/$(KVER)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD)
clean:
	rm -rf *.o *.mod.c *.ko *.symvers *.order *.markers *~

endif
