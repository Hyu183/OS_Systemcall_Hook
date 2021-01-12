# HOOK SYSCALL OPEN AND WRITE

## Cài đặt và chạy thử
### Cài đặt
Mở terminal và di chuyển đến thư mục `SourceCode/Hook`. Tiến hành chạy lệnh sau để biên dịch.
```
$ make
```
Sau khi đã biên dịch xong, bắt đầu lắp vào kernel
```
$ sudo insmod hook.ko
```
### Chạy thử
Chạy chương trình test bằng lệnh
```
$ sudo ./test
```
### Tháo module
Chạy lệnh sau đây để tháo ra khỏi Kernel
```
$ sudo rmmod hook
```
Dọn dẹp
```
$ make clean
```
