#include <stdio.h>
#include <stdlib.h>

#include "common/common.h"

#include "sum/sum.h"
#include "human/human.h"

static zlog_category_t* log = NULL;

static zlog_category_t* get_zlog() {
    // log
    if (NULL == log) {
        log = init_zlog();
    }
    return log;
}

int main() {

    zlog_info(get_zlog(), "hello, zlog");

    printf("\n%d + %d = %d", 1, 2, sum(1, 2));
    printf("\nhuman: %d\n", human());
    printf("\nhello world\n\n");

    zlog_fini();
    return 0;
}