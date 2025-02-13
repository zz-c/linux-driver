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