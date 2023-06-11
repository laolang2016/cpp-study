#include <stdio.h>
#include <stdlib.h>

#include "common/zlog_conf.h"

const char* zlog_conf = "[formats]\n\
simple = \"%d().%ms %p %V [%F:%L] - %m%n\"\n\
[rules]\n\
my_cat.* >stdout; simple\b\
*.*     \"app.log\", 10MB * 0 ~ \"app-%d(%Y%m%d).#2s.log\"";

static zlog_category_t* handler = NULL;

zlog_category_t* init_zlog() {
    if (NULL == handler) {
        int rc;
        // rc = zlog_init(zlog_conf);
        rc = zlog_init("zlog.conf");

        if (rc) {
            printf("init zlog failed\n");
            exit(EXIT_FAILURE);
        }
    }

    handler = zlog_get_category("my_cat");

    if (!handler) {
        zlog_fini(); // 释放zlog
        printf("zlog get cat failed\n");
        exit(EXIT_FAILURE);
    }

    return handler;
}