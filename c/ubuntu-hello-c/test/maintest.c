#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/TestDB.h>

// #include "common/common.h"

#include "test_sum.h"

// 待测试方法
int add(int x, int y) {
    return x + y;
}

// 测试方法
void test_add() {
    CU_ASSERT(3 == add(1, 2));
}

// suite 初始化
int suite_success_init() {
    return 0;
}

// suite 清理
int suite_success_clean() {
    return 0;
}

// 测试组
CU_TestInfo testcase[] = {
    {"test_for_add:", test_add},
    CU_TEST_INFO_NULL
};

CU_TestInfo test_sum_case[] = {
    {"test_for_sum:", test_sum},
    CU_TEST_INFO_NULL
};

// 测试套件
CU_SuiteInfo suites[] = {
    {"testSuite1", suite_success_init, suite_success_clean, NULL, NULL, testcase},
    {"test_suite_sum", suite_success_init, suite_success_clean, NULL, NULL, test_sum_case},
    CU_TEST_INFO_NULL
};

int main(int argc, char** argv) {
    // test main
    if (CU_initialize_registry()) {
        fprintf(stderr, " Initialization of Test Registry failed.");
        exit(EXIT_FAILURE);
    } else {
        assert(NULL != CU_get_registry());
        assert(!CU_is_test_running());

        if (CUE_SUCCESS != CU_register_suites(suites)) {
            exit(EXIT_FAILURE);
        }

        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();

        CU_cleanup_registry();
        return CU_get_error();
    }
    return 0;
}