## 第一个程序

### 源码
```c linenums="1" title="main.c"
/*
** This program reads input lines from the standard input and prints
** each input line, followed by just some portions of the lines, to
** the standard output.
**
** The first input is a list of column numbers, which ends with a
** negative number.  The column numbers are paired and specify
** ranges of columns from the input line that are to be printed.
** For example, 0 3 10 12 -1 indicates that only columns 0 through 3
** and columns 10 through 12 will be printed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COLS    20  /* max # of columns to process */
#define MAX_INPUT   1000    /* max len of input & output lines */

int read_column_numbers(int columns[], int max);
void    rearrange(char* output, char const* input,
                  int n_columns, int const columns[]);

int
main(void) {
    int n_columns;      /* # of columns to process */
    int columns[MAX_COLS];  /* the columns to process */
    char    input[MAX_INPUT];   /* array for input line */
    char    output[MAX_INPUT];  /* array for output line */

    /*
    ** Read the list of column numbers
    */
    n_columns = read_column_numbers(columns, MAX_COLS);

    /*
    ** Read, process and print the remaining lines of input.
    */
    while (gets(input) != NULL) {
        printf("Original input : %s\n", input);
        rearrange(output, input, n_columns, columns);
        printf("Rearranged line: %s\n", output);
    }

    return EXIT_SUCCESS;
}

/*
** Read the list of column numbers, ignoring any beyond the specified
** maximum.
*/
int
read_column_numbers(int columns[], int max) {
    int num = 0;
    int ch;

    /*
    ** Get the numbers, stopping at eof or when a number is < 0.
    */
    while (num < max && scanf("%d", &columns[num]) == 1
           && columns[num] >= 0)
        num += 1;

    /*
    ** Make sure we have an even number of inputs, as they are
    ** supposed to be paired.
    */
    if (num % 2 != 0) {
        puts("Last column number is not paired.");
        exit(EXIT_FAILURE);
    }

    /*
    ** Discard the rest of the line that contained the final
    ** number.
    */
    while ((ch = getchar()) != EOF && ch != '\n')
        ;

    return num;
}

/*
** Process a line of input by concatenating the characters from
** the indicated columns.  The output line is then NUL terminated.
*/
void
rearrange(char* output, char const* input,
          int n_columns, int const columns[]) {
    int col;        /* subscript for columns array */
    int output_col; /* output column counter */
    int len;        /* length of input line */

    len = strlen(input);
    output_col = 0;

    /*
    ** Process each pair of column numbers.
    */
    for (col = 0; col < n_columns; col += 2) {
        int nchars = columns[col + 1] - columns[col] + 1;

        /*
        ** If the input line isn't this long or the output
        ** array is full, we're done.
        */
        if (columns[col] >= len ||
            output_col == MAX_INPUT - 1)
            break;

        /*
        ** If there isn't room in the output array, only copy
        ** what will fit.
        */
        if (output_col + nchars > MAX_INPUT - 1)
            nchars = MAX_INPUT - output_col - 1;

        /*
        ** Copy the relevant data.
        */
        strncpy(output + output_col, input + columns[col],
                nchars);
        output_col += nchars;
    }

    output[output_col] = '\0';
}
```

### 构建脚本
=== "CMakeLists.txt"
    ```cmake linenums="1"
    cmake_minimum_required(VERSION 3.25)

    project(helloc C)

    set(CMAKE_C_STANDARD 17)
    set(CMAKE_C_STANDARD_REQUIRED True)
    set(CMAKE_C_EXTENSIONS OFF)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

    include_directories(${CMAKE_SOURCE_DIR})

    aux_source_directory(. SRCS)

    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

    add_executable(${PROJECT_NAME} ${SRCS})
    ```
=== "run.sh"
    ```shell linenums="1"
    #!/bin/bash

    if [ -d build ]; then
    rm -r build
    fi

    cmake -S . -B build && cmake --build build

    ./build/bin/helloc
    ```

### 运行效果

```shell
laolang@laolang-pc:~/tmp$ l
总计 16K
-rw-rw-r-- 1 laolang laolang  398 2023-06-02 07:55:51 CMakeLists.txt
-rwxrwxr-x 1 laolang laolang   85 2023-06-02 07:58:43 format.sh*
-rw-rw-r-- 1 laolang laolang 3.4K 2023-06-02 07:58:46 main.c
-rwxrwxr-x 1 laolang laolang  142 2023-06-02 08:06:46 run.sh*
laolang@laolang-pc:~/tmp$ ./run.sh 
-- The C compiler identification is GNU 11.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/laolang/tmp/build
[ 50%] Building C object CMakeFiles/helloc.dir/main.c.o
/home/laolang/tmp/main.c: In function ‘main’:
/home/laolang/tmp/main.c:38:12: warning: implicit declaration of function ‘gets’; did you mean ‘fgets’? [-Wimplicit-function-declaration]
   38 |     while (gets(input) != NULL) {
      |            ^~~~
      |            fgets
/home/laolang/tmp/main.c:38:24: warning: comparison between pointer and integer
   38 |     while (gets(input) != NULL) {
      |                        ^~
[100%] Linking C executable bin/helloc
/usr/bin/ld: CMakeFiles/helloc.dir/main.c.o: in function `main':
main.c:(.text+0xa9): 警告： the `gets' function is dangerous and should not be used.
[100%] Built target helloc
4 9 12 20 -1
abcdefghijklmnopqrstuvwxyz
Original input : abcdefghijklmnopqrstuvwxyz
Rearranged line: efghijmnopqrstu
Hello there, how are you?
Original input : Hello there, how are you?
Rearranged line: o ther how are 
I am fine, thanks.
Original input : I am fine, thanks.
Rearranged line:  fine,hanks.
See you!
Original input : See you!
Rearranged line: you!
Bye
Original input : Bye
Rearranged line: 
-1
Original input : -1
Rearranged line: 
^C
laolang@laolang-pc:~/tmp$ 
```

### 修正
添加两个文件

=== "global.h"
    ```c linenums="1"
    #ifndef _GLOBAL_H_
    #define _GLOBAL_H_

    /* max # of columns to process */
    extern const int MAX_COLS;
    /* max len of input & output lines */
    extern const int MAX_INPUT;

    #endif
    ```
=== "global.c"
    ```c linenums="1"
    #include "global.h"

    const int MAX_COLS = 20;
    const int MAX_INPUT = 1000;
    ```
`main.c` 修改如下
> 1. 将 `#define` 宏定义改为全局常量
> 2. 使用 `fgets` 替代 `gets`

![](/assets/image/c/prepare/c_and_pointer/simple_program/01.png)

