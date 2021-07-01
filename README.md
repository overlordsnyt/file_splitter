# 纯C的文本文件分割器

*本来是用来分割多行电话号码txt的*

## 下载

[https://github.com/overlordsnyt/file_splitter/releases]()

## 用法

### 分割器：

```shell
./splitter whole_file.txt file_lines read_line_max_length
```

把要分割的文件‘whole_file.txt’按file_lines行为一个新文件分割，每行可能的最大字节数为read_line_max_length。三个调用参数缺一不可。

### *号码生成器*：

```shell
./phonegen
```

直接运行生成字节数小于生成内存缓冲BUFSIZ=4096字节数的一个号码文件。

*本程序仅做测试用，号码为随机号码，不具有现实意义。*

## 编译说明

本程序已通过编译：

- MSVC14.16.27023 for VS17
- gcc 9.3.0 for WSL Ubuntu-20.04

## 特性

1. 多线程执行分割任务。
1. 跨平台的编译，通过定义宏在编译时无感跨平台。

## 待改进

- [ ] 可配置的线程数、BUFSIZ大小
- [ ] phonegen在每次生成随机数的时候设定随机数种子的优化