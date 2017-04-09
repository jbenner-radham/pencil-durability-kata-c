#include <check.h>
#include <stdlib.h>
#include "pencil.h"

Suite *kata_suite(void)
{
    Suite *suite = suite_create("kata");
    TCase *tcase = tcase_create("Core");

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
