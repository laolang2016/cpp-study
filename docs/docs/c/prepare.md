## CUnit

### 参考资料
官网 : [https://cunit.sourceforge.net/](https://cunit.sourceforge.net/)

github: [https://github.com/jacklicn/CUnit](https://github.com/jacklicn/CUnit)

官方手册: [https://cunit.sourceforge.net/doc/index.html](https://cunit.sourceforge.net/doc/index.html)

中文手册: [【单元测试】CUnit用户手册（中文）](https://blog.csdn.net/benkaoya/article/details/95887879)

简明教程: [【单元测试】CUnit单元测试框架（不支持mock功能）](https://blog.csdn.net/benkaoya/article/details/95870801)

[ubuntu下安装CUnit出现的问题及解决](https://www.codenong.com/cs106365824)

### 安装

```shell
sudo apt-get update
sudo apt-get install build-essential automake autoconf libtool
mv configure.in configure.ac
aclocal
autoconf 
autoheader 
libtoolize --automake --copy --debug --force
automake --add-missing
automake
./configure 
make
sudo make install
```

### 测试
```c linenums="1" title="test.c"
#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

/* 被测试的函数，在当中故意安装了一个BUG */
static int sum(int a, int b)
{
    if (a > 4)
    {
        return 0;
    }
    return (a + b);
}

static int suite_init(void)
{
    return 0;
}

static int suite_clean(void)
{
    return 0;
}

static void test_sum(void)
{
    CU_ASSERT_EQUAL(sum(1, 2), 3);
    CU_ASSERT_EQUAL(sum(5, 2), 7);
}

int main()
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    /* add a suite to the registry */
    pSuite = CU_add_suite("suite_sum", suite_init, suite_clean);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test_sum", test_sum)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // basic
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // automated
    CU_list_tests_to_file();
    CU_automated_run_tests();

    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
```

编译

```shell
 gcc test.c `pkg-config --libs --cflags cunit` -o test
```

此时控制台有了 basic 模式的输出, 并且有了 automated 模式的 xml 文件

然后从安装包复制如下几个文件, 和 cunit 输出的 xml 同级
* CUnit-List.dtd  
* CUnit-List.xsl  
* CUnit-Run.dtd  
* CUnit-Run.xsl

在本地起一个服务器, 比如 npm 的 serve , 两个文件现实效果如下

![](/assets/image/c/prepare/01.png)

![](/assets/image/c/prepare/02.png)

## GCOV+LCOV 代码调试和覆盖率统计工具

### 参考
[GCOV+LCOV 代码调试和覆盖率统计工具](https://blog.csdn.net/gatieme/article/details/78368667)

### 代码
=== "cunit_sample.c"
    ```c linenums="1"
    #include <stdio.h>
    #include <string.h>
    #include <CUnit/Basic.h>
    #include <CUnit/Automated.h>

    #include "module.h"

    static int suite_init(void)
    {
        return 0;
    }

    static int suite_clean(void)
    {
        return 0;
    }

    static void test_sum(void)
    {
        CU_ASSERT_EQUAL(sum(1, 2), 3);
        CU_ASSERT_EQUAL(sum(5, 2), 7);
    }

    int main()
    {
        CU_pSuite pSuite = NULL;

        /* initialize the CUnit test registry */
        if (CUE_SUCCESS != CU_initialize_registry())
        {
            return CU_get_error();
        }

        /* add a suite to the registry */
        pSuite = CU_add_suite("suite_sum", suite_init, suite_clean);
        if (NULL == pSuite)
        {
            CU_cleanup_registry();
            return CU_get_error();
        }

        /* add the tests to the suite */
        if ((NULL == CU_add_test(pSuite, "test_sum", test_sum)))
        {
            CU_cleanup_registry();
            return CU_get_error();
        }

        // basic
        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();

        // automated
        CU_list_tests_to_file();
        CU_automated_run_tests();

        /* Clean up registry and return */
        CU_cleanup_registry();
        return CU_get_error();
    }
    ```
=== "module.c"
    ```c linenums="1"
    #include "module.h"
    int sum(int a, int b)
    {
        if (a > 4)
        {
            return 0;
        }
        if( a < 0 )
        {
            return -1;
        }
        return (a + b);
    }
    ```
=== "module.h"
    ```c linenums="1"
    #ifndef __CUNIT_SAMPLE_MODULE_
    #define __CUNIT_SAMPLE_MODULE_
    int sum(int a, int b);
    #endif
    ```

### 编译和运行
```shell
gcc -g -c module.c -o module.o `pkg-config --cflags cunit` -fprofile-arcs -ftest-coverage
gcc -g -c cunit_sample.c -o cunit_sample.o `pkg-config --cflags cunit` -fprofile-arcs -ftest-coverage
gcc module.o cunit_sample.o -o test `pkg-config --libs cunit` -fprofile-arcs -ftest-coverage -lpthread
./test
```
!!! note
    必须要运行才可以

### gcov + lcov

### 生成覆盖率信息
上一步已经生成了 `.gcda` 文件, 此文件包含程序基本块跳转信息, 现在生成覆盖率信息
```shell
gcov module.c
gcov cunit_sample.c
```

现在可以查看覆盖率信息

```shell
laolang@laolang-pc:~/code/c/hello-c/one$ cat module.c.gcov 
        -:    0:Source:module.c
        -:    0:Graph:module.gcno
        -:    0:Data:module.gcda
        -:    0:Runs:1
        -:    1:#include "module.h"
        4:    2:int sum(int a, int b)
        -:    3:{
        4:    4:    if (a > 4)
        -:    5:    {
        2:    6:        return 0;
        -:    7:    }
        2:    8:    if( a < 0 )
        -:    9:    {
    #####:   10:        return -1;
        -:   11:    }
        2:   12:    return (a + b);
        -:   13:}
laolang@laolang-pc:~/code/c/hello-c/one$ 
```

### 生成文档
```shell
lcov -d . -t '我的第一个测试' -o app.info -b . -c
genhtml app.info -o cc_result
```

打开 `cc_result/index.html`

![](/assets/image/c/prepare/03.png)

![](/assets/image/c/prepare/04.png)

## zlog

github: [https://github.com/HardySimpson/zlog/](https://github.com/HardySimpson/zlog/)

中文手册: [http://hardysimpson.github.io/zlog/UsersGuide-CN.html](http://hardysimpson.github.io/zlog/UsersGuide-CN.html)

### 安装
```shell
make
sudo make install
```

### 测试

=== "test.c"
    ```c linenums="1"
    #include <stdio.h>
    #include <zlog.h>

    int main()
    {
        int rc;
        zlog_category_t *c;

        rc = zlog_init("test_hello.conf");

        if (rc)
        {

            printf("init failed\n");
            return -1;
        }

        c = zlog_get_category("my_cat");

        if (!c)
        {

            printf("get cat fail\n");

            zlog_fini();
            return -2;
        }

        zlog_info(c, "hello, zlog");

        zlog_fini();

        return 0;
    }
    ```
=== "test_hello.conf"
    ```conf linenums="1"
    [formats]

    simple = "%d().%ms %p %V [%F:%L] - %m%n"

    [rules]

    my_cat.DEBUG    >stdout;    simple
    *.*     "app.log", 10MB * 0 ~ "app-%d(%Y%m%d).#2s.log"
    ```

`*.*     "app.log", 10MB * 0 ~ "app-%d(%Y%m%d).#2s.log"` 含义为: 日志名称为 app.log , 日志文件没10MB开始转当, 转档格式为 app-2023-05-04.01.log

编译
```shell
gcc test.c -I/usr/local/include -L/usr/local/lib -lzlog -o test
```

输出如下
```shell
laolang@laolang-pc:~/code/c/hello-c/one$ ./test 
2023-06-01 07:51:41.599 34977 INFO [test.c:29] - hello, zlog
laolang@laolang-pc:~/code/c/hello-c/one$ cat app.log 
2023-06-01 07:51:41 INFO [34977:test.c:29] hello, zlog
laolang@laolang-pc:~/code/c/hello-c/one$ 
```

**zlog-chk-conf**可以检查配置文件是否正确
```shell
laolang@laolang-pc:~/code/c/hello-c/one$ zlog-chk-conf test_hello.conf 
06-01 07:55:22 ERROR (35128:rule.c:721) in conf file can't find format[imple], pls check
06-01 07:55:22 ERROR (35128:conf.c:538) zlog_rule_new fail [my_cat.DEBUG    >stdout;    imple]
06-01 07:55:22 ERROR (35128:conf.c:340) parse configure file[test_hello.conf]line_no[7] fail
06-01 07:55:22 ERROR (35128:conf.c:341) line[my_cat.DEBUG    >stdout;    imple]
06-01 07:55:22 ERROR (35128:conf.c:177) zlog_conf_build_with_file fail
06-01 07:55:22 ERROR (35128:zlog.c:93) zlog_conf_new[test_hello.conf] fail
06-01 07:55:22 ERROR (35128:zlog.c:135) zlog_init_inner[test_hello.conf] fail
06-01 07:55:22 ERROR (35128:zlog.c:150) ------zlog_init fail end------

---[test_hello.conf] syntax error, see error message above
laolang@laolang-pc:~/code/c/hello-c/one$ zlog-chk-conf test_hello.conf 
--[test_hello.conf] syntax right
laolang@laolang-pc:~/code/c/hello-c/one$ 
```


## AStyle

### 参考资料

官网: [https://astyle.sourceforge.net/](https://astyle.sourceforge.net/)

Google 开源项目风格指南——中文版: [https://zh-google-styleguide.readthedocs.io/en/latest/](https://zh-google-styleguide.readthedocs.io/en/latest/)

[Artistic Style 使用教程（中文版）](https://blog.csdn.net/qq_39366020/article/details/107035023)

[Astyle 快速入门，常用指令](https://www.cnblogs.com/qiyuexin/p/8206510.html)

[AStyle自动排版代码方法（超详细）](https://blog.csdn.net/gsp1004/article/details/107024332)

### 安装
```shell
tar xf astyle-3.3.1.tar.bz2
cd build
cd gcc
make
sudo make install
```

### 配置

```ini
# braces and indent
style=google
# 缩进使用 4 个空格
indent=spaces=4

# indentation ----------------------------------------------------------------------------------------------------------
# 缩进 switch case
indent-switches
indent-continuation=4
indent-preproc-block
indent-preproc-define
# 代码宽度
min-conditional-indent=0
max-continuation-indent=120
# 注释和代码一起缩进
indent-col1-comments

# padding --------------------------------------------------------------------------------------------------------------
# 操作符两端插入一个空格
pad-oper
# 在if.for,while等条件或循环语句关键字和括号之间插入空格
pad-header
unpad-paren
# 指针贴近类型
align-pointer=type

# formatting
# 从同一行中的语句中断开一行标题（例如，“ if”，“ while”，“ else”，…）
break-one-line-headers
keep-one-line-blocks
# 从同一行中的语句中断开一行标题（例如，“ if”，“ while”，“ else”，…）
keep-one-line-statements
# 将制表符转换为空格，插入的空格数将保持制表符的间距。引号中的制表符不会被替换
convert-tabs
#close-templates
```

### vscode 配置
```json
{
    //配置：格式化代码的语言
    "astyle.additional_languages": [
        "c",
        "cpp",
    ],
    //配置：代码格式化风格
    "astyle.cmd_options": [
        "style=google",
        "indent=spaces=4", //缩进使用 4 个空格
        "indent-switches", // 缩进 switch case
        "indent-continuation=4",
        "indent-preproc-block", // 缩进在零级别括号和名称空间中的预编译块
        "indent-preproc-define", //缩进以反斜杠结尾的多行预处理器定义
        "min-conditional-indent=0", // 代码宽度
        "max-continuation-indent=120", // 代码宽度
        "indent-col1-comments", // 注释和代码一起缩进
        "pad-oper", // 操作符两端插入一个空格
        "pad-header", //在if.for,while等条件或循环语句关键字和括号之间插入空格
        "unpad-paren", //在内部和外部的括号周围插入空格。如有可能，任何行尾注释都将保留在原始列中
        "align-pointer=type", // 指针贴近类型
        "break-one-line-headers", //从同一行中的语句中断开一行标题（例如，“ if”，“ while”，“ else”，…）
        "keep-one-line-blocks",
        "keep-one-line-statements", // 从同一行中的语句中断开一行标题（例如，“ if”，“ while”，“ else”，…）
        "convert-tabs", //将制表符转换为空格，插入的空格数将保持制表符的间距。引号中的制表符不会被替换
    ],
}
```

## 上述功能整合

### 代码地址
[https://gitcode.net/u014254963/cpp-study/-/tree/master/c/ubuntu-hello-c](https://gitcode.net/u014254963/cpp-study/-/tree/master/c/ubuntu-hello-c)

## todo

### CMocka

**参考资料**

[【单元测试】CMocka单元测试框架（支持mock功能）](https://blog.csdn.net/benkaoya/article/details/100933141)

### clang-format

**参考资料**
[Clang-format 配置文件指南](https://juejin.cn/post/7158712365175799839)

[使用 clang-format 进行 C++ 代码风格管理](https://zhuanlan.zhihu.com/p/514541589)
