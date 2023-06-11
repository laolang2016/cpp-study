#include "common/zlog_conf.h"

#include "sum/sum.h"

int sum(int x, int y) {
    zlog_category_t* log = init_zlog();
    zlog_info(log, "call sum");
    if (x > 100) {
        return x + 1 + y;
    }

    return x + y;
}