

## 編譯 module
在 kernel_test 目錄下執行 make，看到以下的訊息就算是完成編譯了
```
make
make -C /usr/src/linux-headers-3.19.0-31-generic/ M=/home/jerry/kernel_test modules  make[1]: Entering directory /usr/src/linux-headers-3.19.0-31-generic    Building modules, stage 2.    MODPOST 1 modules   make[1]: Leaving directory/usr/src/linux-headers-3.19.0-31-generic
```
用 ls 可以看到編好的檔案們
```
hello.c hello.ko hello.mod.c hello.mod.o hello.o Makefile modules.order Module.symvers
```

## 載入/移除 module
使用 insmod 指令來載入 hello.ko
```
sudo insmod hello.ko
```
接著用 lsmod 指令來確認 module 是否成功載入 因為系統載入的 module 很多，這邊用 grep 來過濾出我們的 hello module，如下所示
```
sudo lsmod | grep "hello"
hello 16384 0
```
最後，把 hello module 移除 使用 rmmod 指令，就可以把 module 移除囉
```
sudo rmmod hello.ko
```
執行完載入與移除的動作，我們回過頭來看看 hello.c 裡頭的 hello_init 和 hello_exit 這裡各呼叫了 printk 這個 function，它會在系統日誌上輸出 KERN_INFO 級別的訊息 可以呼叫 dmesg 指令來察看系統日誌
```
dmesg
...(略)
 [11261.743645] Hello world !
 [12433.528440] Bye !
```
