#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "pencil.h"

START_TEST(test_it_writes_to_paper)
{
    char paper[BUFSIZ] = {0};
    const char *actual = pencil_write_to_paper("Hello world.", paper);
    const char *expected = "Hello world.";

    ck_assert_str_eq(actual, expected);
}
END_TEST

Suite *kata_suite(void)
{
    Suite *suite = suite_create("kata");
    TCase *tcase = tcase_create("Core");

    tcase_add_test(tcase, test_it_writes_to_paper);
    suite_add_tcase(suite, tcase);

    return suite;
}

int main(void)
{
    int number_failed;
    Suite *suite = kata_suite();
    SRunner *srunner = srunner_create(suite);

    srunner_run_all(srunner, CK_NORMAL);

    number_failed = srunner_ntests_failed(srunner);

    srunner_free(srunner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
