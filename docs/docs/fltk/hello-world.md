## 参考
[https://blog.csdn.net/smart_jackli/article/details/128133452](https://blog.csdn.net/smart_jackli/article/details/128133452)

## 安装
**安装依赖库**
```shell
sudo apt-get install build-essential xorg-dev libx11-dev libcairo2-dev
```

**下载**
[https://www.fltk.org/software.php](https://www.fltk.org/software.php)


**安装**
```shell
./configure --enable-debug --enable-gl --enable-shared --enable-threads --enable-xdbe --enable-xft
```

!!! note "相关参数"
    --enable-cygwin :Enable the Cygwin libraries under WIN32

    --enable-debug: Enable debugging code & symbols
    
    --disable-gl: Disable OpenGL support
    
    --enable-shared: Enable generation of shared libraries
    
    --enable-threads: Enable multithreading support
    
    --enable-xdbe: Enable the X double-buffer extension
    
    --enable-xft: Enable the Xft library for anti-aliased fonts under X11
    
    --bindir=/path: Set the location for executables [default = $prefix/bin]
    
    --datadir=/path: Set the location for data files. [default = $prefix/share]
    
    --libdir=/path: Set the location for libraries [default = $prefix/lib]
    
    --includedir=/path: Set the location for include files. [default = $prefix/include]
    
    --mandir=/path: Set the location for man pages. [default = $prefix/man]
    
    --prefix=/dir: Set the directory prefix for files [default = /usr/local]


## hello world

```c++ linenums="1" title="hello.cpp"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
int main(int argc, char **argv) {
    Fl_Window *window = new Fl_Window(340,180);
    Fl_Box *box = new Fl_Box(20,40,300,100,"Hello, World!");
    box->box(FL_UP_BOX);
    box->labelfont(FL_BOLD+FL_ITALIC);
    box->labelsize(36);
    box->labeltype(FL_SHADOW_LABEL);
    window->end();
    window->show(argc, argv);
    return Fl::run();
}
```

**编译**
```shell
fltk-config --compile hello.cpp
```

**运行效果**
![](/assets/image/fltk/hello-world/01.png)
