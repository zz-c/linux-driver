# linux-driver

## 安装必要的开发工具
```bash
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r)
```
build-essential 包含了编译 C 程序的工具。  
linux-headers-$(uname -r) 安装当前运行内核的头文件。  

## 加载和卸载模块
```bash
# 编译模块
make
# 使用 insmod 命令加载内核模块
sudo insmod simple_driver.ko
# 检查模块加载情况
lsmod | grep simple_driver
# 卸载模块
sudo rmmod simple_driver
# 检查内核日志
dmesg | tail
```

## 测试应用程序
```bash
gcc -o simple_driver_test simple_driver_test.c
```

## 设备文件创建
```bash
# c表示字符设备，块设备则用b，100 是主设备号，0 是次设备号
sudo mknod /dev/simple_driver c 100 0
# 使设备文件对所有用户可读写
sudo chmod 666 /dev/simple_driver
# 删除设备文件
sudo rm /dev/simple_driver
```

## 运行测试
```bash
./simple_driver_test
```