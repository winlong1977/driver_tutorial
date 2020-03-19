## Makefile for compiling ko object(s)
##
## Note:
##   VAR_NAME = value    #=> Variable assignment
##   $(VAR_NAME)         #=> Variable reference
##   $(shell usr_cmd)    #=> Execute a shell command and return its result

PWD := $(shell pwd) 
KVERSION := $(shell uname -r)
KERNEL_DIR = /usr/src/linux-headers-$(KVERSION)/

MODULE_NAME = hello
obj-m := $(MODULE_NAME).o

all:
   make -C $(KERNEL_DIR) M=$(PWD) modules
clean:
   make -C $(KERNEL_DIR) M=$(PWD) clean
