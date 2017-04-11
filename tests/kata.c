#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pencil.h"

START_TEST(test_it_writes_to_paper)
{
    char paper[BUFSIZ] = {0};
    const char *actual = pencil_write_to_paper("Hello world.", paper);
    const char *expected = "Hello world.";

    ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_should_append_text_to_the_paper)
{
    char paper[BUFSIZ] = {0};

    strcpy(paper, "She sells sea shells");

    const char *actual = pencil_write_to_paper(" down by the sea shore", paper);
    const char *expected = "She sells sea shells down by the sea shore";

    ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_initializes_a_pencil_with_a_point_durability)
{
    Pencil pencil = {0};
    unsigned int point_durability = 9001;

    pencil_ctor(&pencil, point_durability);
    ck_assert_int_eq(pencil.point_durability, point_durability);
}
END_TEST

START_TEST(test_expends_no_point_durability_writing_spaces)
{
    unsigned int actual = pencil_degradation(PENCIL_SPACE);
    unsigned int expected = 0;

    ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_expends_no_point_durability_writing_newlines)
{
    unsigned int actual = pencil_degradation(PENCIL_NEWLINE);
    unsigned int expected = 0;

    ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_expends_one_point_of_durability_writing_a_lowercase_character)
{
    unsigned int actual = pencil_degradation('a');
    unsigned int expected = 1;

    ck_assert_int_eq(actual, expected);
}
END_TEST

Suite *kata_suite(void)
{
    Suite *suite = suite_create("Pencil Durability Kata");
    TCase *write_tcase = tcase_create("Write");
    TCase *point_degredation_tcase = tcase_create("Point Degradation");

    tcase_add_test(write_tcase, test_it_writes_to_paper);
    tcase_add_test(write_tcase, test_should_append_text_to_the_paper);
    suite_add_tcase(suite, write_tcase);

    tcase_add_test(point_degredation_tcase, test_initializes_a_pencil_with_a_point_durability);
    tcase_add_test(point_degredation_tcase, test_expends_no_point_durability_writing_spaces);
    tcase_add_test(point_degredation_tcase, test_expends_no_point_durability_writing_newlines);
    tcase_add_test(point_degredation_tcase, test_expends_one_point_of_durability_writing_a_lowercase_character);
    suite_add_tcase(suite, point_degredation_tcase);

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
