## 目录结构
```shell
laolang@laolang-pc:~/gitcode/cpp-study/cmake-demos/hello_03$ tree
.
├── CMakeLists.txt
├── include
│   ├── calc
│   │   ├── calc.h
│   │   ├── div.h
│   │   └── sum.h
│   └── xmlparser
│       ├── document.h
│       ├── node.h
│       └── xmlparser.h
└── src
    ├── calc
    │   ├── CMakeLists.txt
    │   ├── div.cpp
    │   └── sum.cpp
    ├── CMakeLists.txt
    ├── main
    │   ├── CMakeLists.txt
    │   └── main.cpp
    └── xmlparser
        ├── CMakeLists.txt
        ├── document.cpp
        └── node.cpp

7 directories, 16 files
laolang@laolang-pc:~/gitcode/cpp-study/cmake-demos/hello_03$ 
```

## CMakeLists.txt
### 顶层 CMakeLists.txt
```cmake linenums="1"
cmake_minimum_required(VERSION 3.0)

project(cpp-hello CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_WITH_INSTALL_RPATH True)

set(lib_calc calc)
set(lib_xmlparser xmlparser)

add_subdirectory(src)
```
### src/CMakeLists.txt
```cmake linenums="1"
add_subdirectory(main)
add_subdirectory(calc)
add_subdirectory(xmlparser)
```

### src/[calc,xmlparser]/CMakeLists.txt
=== "src/calc/CMakeLists.txt"
    ```cmake linenums="1"
    set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

    aux_source_directory(. CALC_SRCS)

    add_library(${lib_calc} SHARED ${CALC_SRCS})

    target_include_directories(${lib_calc} PUBLIC ${PROJECT_SOURCE_DIR}/include)
    target_link_libraries(${lib_calc} ${lib_util})

    set_target_properties(${lib_calc} PROPERTIES VERSION 1.0 SOVERSION 1)
    ```
=== "src/xmlparser/CMakeLists.txt"
    ```cmake linenums="1"
    set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

    aux_source_directory(. XML_PARSER_SRCS)

    add_library(${lib_xmlparser} SHARED ${XML_PARSER_SRCS})

    target_include_directories(${lib_xmlparser} PUBLIC ${PROJECT_SOURCE_DIR}/include)
    target_link_libraries(${lib_xmlparser} ${lib_util})

    set_target_properties(${lib_xmlparser} PROPERTIES VERSION 1.0 SOVERSION 1)
    ```

### src/main/CMakeLists.txt
```cmake linenums="1"
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

aux_source_directory(. SRCS)

add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} ${lib_util} ${lib_calc} ${lib_xmlparser})

set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "\${ORIGIN}/../lib")
```

## 源码

### calc
=== "include/calc/calc.h"
    ```c++ linenums="1"
    #include "calc/div.h"
    #include "calc/sum.h"
    ```
=== "include/calc/sum.h"
    ```c++ linenums="1"
    #ifndef _CALC_SUM_H_
    #define _CALC_SUM_H_

    class Sum{
    public:
        Sum();
        int add(int x, int y);
    };

    #endif
    ```
=== "src/calc/sum.cpp"
    ```c++ linenums="1"
    #include "calc/sum.h"

    Sum::Sum()
    {
    }

    int Sum::add(int x, int y)
    {
        return x + y;
    }
    ```

### xmlparser

**与 calc 并无太大区别**

### main
```c++ linenums="1"
#include <iostream>
#include <memory>

#include "calc/calc.h"
#include "xmlparser/xmlparser.h"

int main(){

    auto calc_sum = std::make_unique<Sum>();
    std::cout << calc_sum->add(1,2) << std::endl;

    auto xmlparser_document = std::make_unique<Document>();
    std::cout << xmlparser_document->parse() << std::endl;

    std::cout << "hello world" << std::endl;

    std::cout << std::endl << "------------------" << std::endl;


    return 0;
}
```

## 重点

### rpath
`set(CMAKE_BUILD_WITH_INSTALL_RPATH True)` [^1]

`set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "\${ORIGIN}/../lib")` [^1]

默认情况下，这个PATH在构建产生的中间文件，是不增加的；而是只对安装的目标有效。如果你想针对构建的中间文件也有效果，可以加上此配置

```shell
laolang@laolang-pc:~/gitcode/cpp-study/cmake-demos/hello_03$ ldd build_release/bin/cpp-hello 
	linux-vdso.so.1 (0x00007ffda47f7000)
	libcalc.so.1 => /home/laolang/gitcode/cpp-study/cmake-demos/hello_03/build_release/bin/../lib/libcalc.so.1 (0x00007f9d41e8b000)
	libxmlparser.so.1 => /home/laolang/gitcode/cpp-study/cmake-demos/hello_03/build_release/bin/../lib/libxmlparser.so.1 (0x00007f9d41e86000)
	libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f9d41c00000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f9d41e53000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f9d41800000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f9d41b19000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f9d41e97000)
laolang@laolang-pc:~/gitcode/cpp-study/cmake-demos/hello_03$ 
```

!!! note 
    此配置最大的作用其实是制作绿色软件

### 生成路径
1. `set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)`
2. `set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)`

bin 路径与lib的相对路径需要与rpath的配置相对应

### link 路径
`target_include_directories(XXX PRIVATE ${PROJECT_SOURCE_DIR}/include)`

参考 [^2]

target_include_directories里面的关键字控制头文件目录传递

target_link_libraries里的关键字控制头文件目录以及链接库传递

!!! note
    PUBLIC:对内对外都公开，可将头文件目录以及链接库传递给连接者

    PRIVATE:对内公开，对外不公开，不可传递头文件目录以及链接库

    INTERFACE:对外公开，对内不公开，可传递头文件目录以及链接库，但内部不可使用头文件及连接库，只能接口传递


[^1]: [https://blog.csdn.net/z296671124/article/details/86699720](https://blog.csdn.net/z296671124/article/details/86699720)
[^2]: [https://blog.csdn.net/weixin_43862847/article/details/119762230](https://blog.csdn.net/weixin_43862847/article/details/119762230)
