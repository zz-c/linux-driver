# linux-driver

## 安装必要的开发工具
```bash
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r)
```
build-essential 包含了编译 C 程序的工具。  
linux-headers-$(uname -r) 安装当前运行内核的头文件。  