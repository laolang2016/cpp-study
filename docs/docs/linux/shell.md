## Shebang

`shebang` 指的是 `#!`

* `#!/bin/sh` : 调用 `/bin/sh`
* `#!/usr/bin/python`: 指定的 `python` 解释器
* `#!/usr/bin/env`: 在不同平台都能正确找到解释器

!!! note "注意事项"
    1. 如果未指定 `shebang`, 脚本执行的时候默认使用当前 `shell` , 也就是 `$SHELL`
    2. 如果 `shebang` 指定了可执行的解释器, 如 `/bin/bash` , '/usr/bin/python', 脚本在执行时, 文件名会作为参数传递给解释器
    3. 如果 `#!` 指定的解释器程序没有可执行权限, 则会报错 `bad interpreter: Permission denied`
    4. 如果 `#!` 指定的解释器程序不是一个可执行文件, 那么解释器程序会被忽略, 转而交给当前的 `$SHELL` 去执行
    5. 如果 `#!` 指定的解释器程序步存在, 那么会报错 `bad interpreter: No such file or directory`
    6. `#!` 之后的解释程序, 需要写其绝对路径
    7. 如果使用指定的解释器去执行脚本,如 `bash test.sh`, 那么 `#!` 会被忽略


## shell 脚本执行方式
* `bash script.sh` 或 `sh script.sh`, 文件本身没有执行权限的时候或者脚本没有指定 `shebang`可以用这个方法, 会启动一个新的bash进程来执行脚本中的命令
* 使用 `相对/绝对` 路径执行脚本, 需要脚本文件有执行权限
* `source script.sh` 或者 `. script.sh`. 在当前shell环境下直接执行`script.sh`脚本中的命令，所以该脚本中定义的变量会在当前shell环境中直接生效


## Hello World
```shell linenums="1"
#!/bin/sh

echo 'hello world'
```

```shell
laolang@laolang-pc:~/code/shell$ ./hello.sh 
hello world
laolang@laolang-pc:~/code/shell$ bash hello.sh 
hello world
laolang@laolang-pc:~/code/shell$ 
```

## 数据类型与变量

### 变量替换
**${var-"another value"}**
> 如果变量`var`没有定义过, 则值为 another value, 定义过了则用原来的值, 如果原值为空, 则新值也为空

```shell linenums="1"
#!/bin/bash

url=
u=${url-"www.baidu.com.cn"}
echo "${u}" # 空

url=www.sina.com.cn
u=${url-"www.baidu.com.cn"}
echo "${u}" # www.sina.com.cn

unset url
u=${url-"www.baidu.com.cn"}
echo "${u}" # www.baidu.com.cn
```

**${var:-"another value"}**
> 如果`var` 没有定义过或者定义了但是为空, 则值为 another value, 定义过了则用原来的值

```shell linenums="1"

#!/bin/bash

url=
u=${url:-"www.baidu.com.cn"}
echo "${u}" # www.baidu.com.cn

url=www.sina.com.cn
u=${url:-"www.baidu.com.cn"}
echo "${u}" # www.sina.com.cn

unset url
u=${url:-"www.baidu.com.cn"}
echo "${u}" # www.baidu.com.cn
```

**${var:="another value"}**
> 如果 `var` 为空或未定义, 则使用新的值

```shell linenums="1"
#!/bin/bash

url=
u=${url:="www.baidu.com.cn"}
echo "${u}" # www.baidu.com.cn

url=www.sina.com.cn
u=${url:="www.baidu.com.cn"}
echo "${u}" # www.sina.com.cn

unset url
u=${url:="www.baidu.com.cn"}
echo "${u}" # www.baidu.com.cn
```

**其他**
```shell
# ${parameter:?word}:当调取变量信息值为空时或未定义,指定为赋值的错误提示信息
[root@m01 ~]# echo ${x:?}
123
[root@m01 ~]# unset x
[root@m01 ~]# echo ${x:?}
-bash: x: parameter null or not set

# ${parameter:+word}:当调取变量信息值为空时或未定义,不做任何处理,否则word字符串将替代变量值
[root@m01 ~]# unset x
[root@m01 ~]# echo ${x:+哈哈哈}

[root@m01 ~]# x=666
[root@m01 ~]# echo ${x:+哈哈哈}
哈哈哈
```


### 特殊变量
1. `$0`: 当前执行的命令或脚本的名称
2. `$1`, `$2`, `$3`, ...: 命令行参数列表中的第 1, 2, 3, ... 个参数，其中 `$1` 指的是第一个参数，以此类推。
3. `$#`: 命令行参数的数量
4. `$@`: 将命令行的所有参数作为一个列表返回，每个参数是一个单独的字符串
5. `$*`: 将命令行的所有参数作为一个单一的字符串返回
6. `$?`: 上一个命令的退出状态码（返回值），如果上一个命令成功执行则返回 0

### 单双引号
* ""  弱引用,引号的特殊字符有意义
* ''	强引用,引号内所有的特殊字符都取消意义

```shell linenums="1"
#!/bin/sh

myvar=hello
echo "my var is : ${myvar}"
echo 'my var is : ${myvar}'
```

```
laolang@laolang-pc:~/code/shell$ ./hello.sh 
my var is : hello
my var is : ${myvar}
laolang@laolang-pc:~/code/shell$
```

### 数组
#### 普通数组
```shell linenums="1"
#!/bin/bash

# 第一种定义方式 #################################################################
echo '------------------------'
myarr=(age 18 grade 7)
# 输出第一个
echo "${myarr}"
echo "${myarr[0]}"

# 输出其他
echo "${myarr[1]}"
echo "${myarr[2]}"
echo "${myarr[3]}"

# 第二种定义方式 #################################################################
echo '------------------------'
myarr2=([0]="age" [1]=18)
echo "${myarr2[0]}"
echo "${myarr2[1]}"

# 第三种定义方式 #################################################################
echo '------------------------'
myarr3[0]=age
myarr3[1]=18
echo "${myarr3[0]}"
echo "${myarr3[1]}"

# 第四种定义方式 #################################################################
echo '------------------------'
myarr4=(`ls .`)
echo "${myarr4[0]}"
```

```shell
laolang@laolang-pc:~/code/shell$ ./hello.sh 
------------------------
age
age
18
grade
7
------------------------
age
18
------------------------
age
18
------------------------
hello.sh
laolang@laolang-pc:~/code/shell$ 
```

也可以反向索引
```shell linenums="1"
#!/bin/bash

myarr=(age 18 grade 7)
# 输出第一个
echo "${myarr[-1]}"
echo "${myarr[-2]}"
echo "${myarr[-3]}"
```

```shell
laolang@laolang-pc:~/code/shell$ ./hello.sh 
7
grade
18
laolang@laolang-pc:~/code/shell$ 
```

#### 关联数组
```shell linenums="1"
#!/bin/bash

declare -A myarr # 定义关联数组
myarr["name"]="laolang"
myarr["age"]=18

echo "${myarr["name"]}"
echo "${myarr["age"]}"
```

```shell
laolang@laolang-pc:~/code/shell$ ./hello.sh 
laolang
18
laolang@laolang-pc:~/code/shell$ 
```

### 字符串相关

#### 字符串长度计算
```shell linenums="1"
#!/bin/bash

myvar='This is a bash script'
echo "myvar is :$myvar"
echo '--------------------------------------------------------------------------'
len1=${#myvar}
echo "$len1"

echo '--------------------------------------------------------------------------'
len2=$(echo "$myvar" | wc -L)
echo "$len2"

echo '--------------------------------------------------------------------------'
len3=$(echo "$myvar" | awk '{print length}')
echo "$len3"

echo '--------------------------------------------------------------------------'
len4=$(expr length "$myvar")
echo "$len4"
```

#### 切片

```shell linenums="1"
#!/bin/bash

myvar='This is a bash script'
echo "${myvar:1}" # his is a bash script
echo "${myvar:1:3}" # his
```
!!! note
    shell 切片步长为 1, 且无法指定步长

#### 截断
```shell linenums="1"
#!/bin/bash

myvar='www.sina.com.cn'
# 去除左边 ----------------------------------------------------------------------
echo ${myvar#www.} # sina.com.cn
echo ${myvar#*w} # 非贪婪, ww.sina.com.cn
echo ${myvar##*w} # 贪婪, .sina.com.cn

# 去除右边 ----------------------------------------------------------------------
echo ${myvar%.cn} # www.sina.com
echo ${myvar%.*} # 非贪婪, www.sina.com
echo ${myvar%%.*} # 贪婪, www
```

#### 替换
```shell linenums="1"
#!/bin/bash

myvar='www.sina.com.cn'
echo ${myvar/sina/baidu} # 非贪婪, www.baidu.com.cn
echo ${myvar//n/N} # 贪婪, www.siNa.com.cN
```

## 分支语句
### if
```shell linenums="1"
#!/bin/bash

age=19
if [ $age -lt 18 ]; then
        echo "too young";
elif [ $age -eq 18 ];then
        echo "just right";
else
        echo "too old";
fi
```

### 循环
#### while
```shell linenums="1"
#!/bin/bash

age=15

while [ $age -lt 18 ]; do
        echo "${age} is too young"
        age=$((age + 1))
done
echo "${age} is just right"
```

#### for
```shell linenums="1"
#!/bin/bash

for ((i = 1; i <= 3; i++)); do
        echo "${i}"
done

for i in {1..3}; do
        echo "${i}"
done
```

## 用户输入
```shell linenums="1"
#!/bin/bash

while getopts :ab:cd opt; do
        case "$opt" in
        a) echo "Found the -a option" ;;
        b) echo "Found the -a option. with value $OPTARG" ;;
        c) echo "Found the -c option" ;;
        d) echo "Found the -d option" ;;
        *) ;;
        esac
done
```

```shell
laolang@laolang-pc:~/code/shell$ ./hello.sh -a -b "hello world" -c -d -s -g
Found the -a option
Found the -a option. with value hello world
Found the -c option
Found the -d option
laolang@laolang-pc:~/code/shell$ 
```

## 函数
### 基本使用
```shell linenums="1"
#!/bin/bash

# 无参 无返回
function f1() {
        echo 'hello world'
}

f1

# 无参 带返回, 函数返回值只能在 0~255 之间
function f2() {
        echo "hello world"
        return $?
}

f2
echo $?

# 带参数
function f3() {
        echo "hello: $1"
}

f3 "world"
```

### 创建库

=== "引入"
    ```shell linenums="1" title="hello.sh"
    #!/bin/bash

    source ./myfuncs.sh

    f1
    ```
=== "定义函数"
    ```shell linenums="1" title="myfuncs.sh"
    #!/bin/bash

    # 无参 无返回
    function f1() {
            echo 'hello world'
    }
    ```