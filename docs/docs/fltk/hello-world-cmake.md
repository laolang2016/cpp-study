## 代码仓库
> [https://gitcode.net/u014254963/cpp-study/-/tree/master/fltk-demos/hello-world-cmake](https://gitcode.net/u014254963/cpp-study/-/tree/master/fltk-demos/hello-world-cmake)
## 目录结构
```shell
laolang@laolang-pc:~/gitcode/cpp-study/fltk-demos/hello-world-cmake$ tree
.
├── CMakeLists.txt
├── include
│   └── xmlparser
│       ├── document.h
│       ├── node.h
│       └── xmlparser.h
├── scripts
│   └── copy_fltk_lib.py
└── src
    ├── CMakeLists.txt
    ├── main
    │   ├── CMakeLists.txt
    │   └── main.cpp
    └── xmlparser
        ├── CMakeLists.txt
        ├── document.cpp
        └── node.cpp

6 directories, 11 files
laolang@laolang-pc:~/gitcode/cpp-study/fltk-demos/hello-world-cmake$ 
```

## python 脚本
```python linenums="1" title="copy_fltk_lib.py"
#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
import os
import subprocess

if __name__ == '__main__':
	print('-- copy fltk libs')
	# 工程路径
	proj_path = sys.argv[1]
	# 构建路径
	build_path = sys.argv[2]
	# 构建后库存放路径
	lib_path = build_path + '/lib'
	# cmake FindFLTK 查找到的 fltk 库列表, 包含系统库
	fltk_cmake_libs = sys.argv[3]
	# 可执行程序名称
	app_name = sys.argv[4]

	# lib 目录不存在则创建
	if not os.path.exists(lib_path):
		os.makedirs(lib_path)

	# 过滤 fltk 库路径列表
	fltk_cmake_libs = fltk_cmake_libs.split(";")
	fltk_libs = []
	for lib in fltk_cmake_libs:
		if "fltk" in lib:
			fltk_libs.append(lib)
	# print(fltk_libs)

	# 执行 ldd , 查找可执行程序需要的 fltk 库
	ldd_command = 'ldd ' + build_path + '/bin/' + app_name
	status, ldd_res =subprocess.getstatusoutput(ldd_command)
	if 0 != status:
		print("ldd app failed", file = sys.stderr )
		exit(1)
	ldd_res = ldd_res.split("\n")
	need_fltk_libs = []
	for lib in ldd_res:
		if "fltk" in lib:
			need_fltk_libs.append(lib.split("=")[0].strip())
	# print(need_fltk_libs)

	# 复制 ftlk 到 lib 路径
	for lib_sys in fltk_libs:
		for lib_need in need_fltk_libs:
			lib_name = lib_need.split(".")[0] + ".so" 
			if lib_name in lib_sys:
				command = "cp " + lib_sys + " " + lib_path + "/" + lib_need
				print("-- " + command)
				status,_ = subprocess.getstatusoutput(command)
				if 0 != status:
					print("copy lib" + lib_name +"failed", file = sys.stderr )
					exit(1)
```

## CMakeLists.txt
```cmake linenums="1" title="顶层 CMakeLists.txt"
cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_WITH_INSTALL_RPATH True)

set(lib_xmlparser xmlparser)

project(cpp-hello CXX)

find_package (Python3 COMPONENTS Interpreter Development REQUIRED)

find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})

add_subdirectory(src)
```

```cmake linenums="1" title="src/main/CMakeLists.txt"
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${FLTK_LIBRARIES} ${lib_xmlparser})

set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "\${ORIGIN}/../lib")

# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/copy_fltk_lib.py "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" "'${FLTK_LIBRARIES}'" "${PROJECT_NAME}"
# )

add_custom_target(copy_fltk_lib ALL
    DEPENDS
        ${PROJECT_NAME}
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/copy_fltk_lib.py "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" "'${FLTK_LIBRARIES}'" "${PROJECT_NAME}"
)
```

## c++
```cmake linenums="1" title="main.cpp"
#include <iostream>
#include <memory>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include "xmlparser/xmlparser.h"

int main(int argc, char **argv)
{
    auto xmlparser_document = std::make_unique<Document>();
    std::cout << xmlparser_document->parse() << std::endl;

    Fl_Window *window = new Fl_Window(340, 180);
    Fl_Box *box = new Fl_Box(20, 40, 300, 100, "Hello, World!");
    box->box(FL_UP_BOX);
    box->labelfont(FL_BOLD + FL_ITALIC);
    box->labelsize(36);
    box->labeltype(FL_SHADOW_LABEL);
    window->end();
    window->show(argc, argv);
    return Fl::run();
}
```

## 运行效果
```shell
laolang@laolang-pc:~/gitcode/cpp-study/fltk-demos/hello-world-cmake$ cmake -S . -B build && cmake --build build
-- The CXX compiler identification is GNU 11.3.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found Python3: /usr/bin/python3.10 (found version "3.10.6") found components: Interpreter Development Development.Module Development.Embed 
-- Found OpenGL: /usr/lib/x86_64-linux-gnu/libOpenGL.so   
-- Found X11: /usr/include   
-- Looking for XOpenDisplay in /usr/lib/x86_64-linux-gnu/libX11.so;/usr/lib/x86_64-linux-gnu/libXext.so
-- Looking for XOpenDisplay in /usr/lib/x86_64-linux-gnu/libX11.so;/usr/lib/x86_64-linux-gnu/libXext.so - found
-- Looking for gethostbyname
-- Looking for gethostbyname - found
-- Looking for connect
-- Looking for connect - found
-- Looking for remove
-- Looking for remove - found
-- Looking for shmat
-- Looking for shmat - found
-- Looking for IceConnectionNumber in ICE
-- Looking for IceConnectionNumber in ICE - found
-- Found FLTK: /usr/local/lib/libfltk_images.so;/usr/local/lib/libfltk_forms.so;/usr/local/lib/libfltk_gl.so;/usr/local/lib/libfltk.so  
-- Configuring done (1.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/laolang/gitcode/cpp-study/fltk-demos/hello-world-cmake/build
[ 20%] Building CXX object src/xmlparser/CMakeFiles/xmlparser.dir/document.cpp.o
[ 40%] Building CXX object src/xmlparser/CMakeFiles/xmlparser.dir/node.cpp.o
[ 60%] Linking CXX shared library ../../lib/libxmlparser.so
[ 60%] Built target xmlparser
[ 80%] Building CXX object src/main/CMakeFiles/cpp-hello.dir/main.cpp.o
[100%] Linking CXX executable ../../bin/cpp-hello
[100%] Built target cpp-hello
-- copy fltk libs
-- cp /usr/local/lib/libfltk.so /home/laolang/gitcode/cpp-study/fltk-demos/hello-world-cmake/build/lib/libfltk.so.1.3
[100%] Built target copy_fltk_lib
laolang@laolang-pc:~/gitcode/cpp-study/fltk-demos/hello-world-cmake$ 
```

![](/assets/image/fltk/hello-world-cmake/01.png)

## 重点

1. cmake 提供了 fltk 的 find 脚本
2. 构建后,使用如下脚本并不能复制 fltk 库, 需要先复制fltk库, 再执行如下脚本
    ```shell
    #!/bin/bash

    LibDir=$PWD"/lib"
    Target=$1

    lib_array=($(ldd $Target | grep -o "/.*" | grep -o "/.*/[^[:space:]]*"))

    $(mkdir $LibDir)

    for Variable in ${lib_array[@]}
    do
        cp "$Variable" $LibDir
    done
    ```
3. 复制脚本有两种方式,一种是 `add_custom_command`, 一种是 `add_custom_target`. 推荐是使用 `add_custom_target`. 原因是 `add_custom_command` 有两个限制：
    * 只有在相同的 `CMakeLists.txt`中, 制定了所有依赖于其输出的目标时才有效
    * 对于不同的独立目标，使用 `add_custom_command` 的输出可以重新执行定制命令. 这可能会导致冲突，应该避免这种情况的发生