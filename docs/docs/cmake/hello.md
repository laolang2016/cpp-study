## 一个最基本的 cmake 程序

> [https://gitcode.net/u014254963/cpp-study/-/tree/master/cmake-demos/hello_01](https://gitcode.net/u014254963/cpp-study/-/tree/master/cmake-demos/hello_01)

### 目录结构
```shell
laolang@laolang-pc:~/gitcode/cpp-study/cmake-demos/hello_01$ l
总计 8.0K
-rw-rw-r-- 1 laolang laolang 158 2023-05-28 11:03:24 CMakeLists.txt
-rw-rw-r-- 1 laolang laolang  82 2023-05-28 11:03:32 main.cpp
laolang@laolang-pc:~/gitcode/cpp-study/cmake-demos/hello_01$ 
```

### c++
```c++ linenums="1" title="main.cpp"
#include <iostream>

int main(){
    std::cout << "hello world" << std::endl;
    return 0;
}
```

### CMakeLists.txt
```cmake linenums="1" title="CMakeLists.txt"
cmake_minimum_required(VERSION 3.25)

# 指定 c++ 版本为 14
set(CMAKE_CXX_STANDARD 14)
# 如果编译器不支持指定的版本, 则终止构建而不是下调版本
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 仅使用标准c++的编译器选项
set(CMAKE_CXX_EXTENSIONS OFF)

project(cpp-hello CXX)

add_executable(${PROJECT_NAME} main.cpp)

```

### 运行
通常来说, 一个 `cmake` 的运行过程如下
```shell
# 创建构建目录
md build
# 进入构建目录
cd build
# 创建 mingw 的 makefile
cmake .. -G "MinGW Makefiles"
# 生成可执行程序
make
# 运行
hello_cmake.exe
```

现在可以一条命令搞定
```shell
cmake -S . -B build && cmake --build build
```
此时已经完成了构建,`./build/cpp-hello` 即可运行程序

!!! info "查看所有构建目标"
    **cmake --build build --target help** 可以查看所有的构建目标


## 多个文件

> [https://gitcode.net/u014254963/cpp-study/-/tree/master/cmake-demos/hello_02](https://gitcode.net/u014254963/cpp-study/-/tree/master/cmake-demos/hello_02)

多个文件的时候只需要修改三行代码

### 目录结构
```shell
laolang@laolang-pc:~/gitcode/cpp-study/cmake-demos/hello_02$ l
总计 16K
-rw-rw-r-- 1 laolang laolang 423 2023-05-28 11:48:42 CMakeLists.txt
-rw-rw-r-- 1 laolang laolang 185 2023-05-28 11:45:42 main.cpp
-rw-rw-r-- 1 laolang laolang 124 2023-05-28 11:45:04 person.cpp
-rw-rw-r-- 1 laolang laolang 148 2023-05-28 11:43:28 person.h
laolang@laolang-pc:~/gitcode/cpp-study/cmake-demos/hello_02$ 
```

### c++
=== "main.cpp"
    ```c++
    #include <iostream>
    #include <memory>

    #include "person.h"


    int main(){
        auto person = std::make_unique<Person>();
        std::cout << person->sayHello() << std::endl;
        return 0;
    }
    ```
=== "person.h"
    ```c++ linenums="1"
    #ifndef _PERSON_H_
    #define _PERSON_H_

    #include <string>

    class Person
    {
    public:
        Person();
        ~Person();
        std::string sayHello();
    };
    #endif
    ```

=== "person.cpp"
    ```c++ linenums="1"
    #include "person.h"

    Person::Person()
    {
    }
    Person::~Person()
    {
    }
    std::string Person::sayHello()
    {
        return "hello world";
    }
    ```

### CMakeLists
```cmake linenums="1" title="CMakeLists.txt"
cmake_minimum_required(VERSION 3.25)

# 指定 c++ 版本为 14
set(CMAKE_CXX_STANDARD 14)
# 如果编译器不支持指定的版本, 则终止构建而不是下调版本
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 仅使用标准c++的编译器选项
set(CMAKE_CXX_EXTENSIONS OFF)

# 添加头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include # (1)!

project(cpp-hello CXX)

# 收集指定目录中所有源文件名称
aux_source_directory(. SRCS) # (2)!

# 使用指定的源文件列表构建可执行程序
add_executable(${PROJECT_NAME} ${SRCS}) # (3)!
```

1. 添加头文件目录

2. 收集指定目录中所有源文件名称

3. 使用指定的源文件列表构建可执行程序

!!! note "注意 aux_source_directory 的副作用"
    正常情况下，生成的构建系统能够感知它何时需要重新运行CMake，因为需要修改CMakeLists.txt来引入一个新的源文件。当源文件仅仅是加到了该路径下，但是没有修改这个CMakeLists.txt文件，使用者只能手动重新运行CMake来产生一个包含这个新文件的构建系统。

!!! note "注意 include_directories 的副作用"
    include_directories 会影响之后所有 CMakeLists.txt,比如子目录的CMakeLists.txt 也会添加指定的头文件目录. 一般放在最外围, 指定特定目标的头文件目录应该使用 `target_include_directories`。
