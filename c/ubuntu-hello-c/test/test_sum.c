#include "test_sum.h"
#include "sum/sum.h"

void test_sum() {
    CU_ASSERT(3 == sum(1, 2));
}