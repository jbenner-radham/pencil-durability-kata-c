#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kata.h"

// Write
START_TEST(test_it_writes_to_paper)
{
    Pencil pencil;
    char paper[BUFSIZ] = {0};
    unsigned int point_durability = 9001;

    pencil_ctor(&pencil, point_durability);

    const char *actual = pencil_write_to_paper(&pencil, "Hello world.", paper);
    const char *expected = "Hello world.";

    ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_should_append_text_to_the_paper)
{
    Pencil pencil;
    char paper[BUFSIZ] = {0};
    unsigned int point_durability = 9001;

    pencil_ctor(&pencil, point_durability);
    strcpy(paper, "She sells sea shells");

    const char *actual = pencil_write_to_paper(&pencil, " down by the sea shore", paper);
    const char *expected = "She sells sea shells down by the sea shore";

    ck_assert_str_eq(actual, expected);
}
END_TEST

// Point Degradation
START_TEST(test_initializes_a_pencil_with_a_point_durability)
{
    Pencil pencil;
    unsigned int point_durability = 9001;

    pencil_ctor(&pencil, point_durability);
    ck_assert_int_eq(pencil.point_durability, point_durability);
}
END_TEST

START_TEST(test_expends_no_point_durability_writing_spaces)
{
    unsigned int actual = pencil_degradation(KATA_SPACE);
    unsigned int expected = 0;

    ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_expends_no_point_durability_writing_newlines)
{
    unsigned int actual = pencil_degradation(KATA_NEWLINE);
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

START_TEST(test_expends_two_points_of_durability_writing_an_uppercase_character)
{
    unsigned int actual = pencil_degradation('A');
    unsigned int expected = 2;

    ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_writes_text_to_a_paper_with_a_point_durability_of_4)
{
    Pencil pencil;
    char paper[BUFSIZ] = {0};
    unsigned int point_durability = 4;

    pencil_ctor(&pencil, point_durability);

    const char *text = "text";
    const char *actual = pencil_write_to_paper(&pencil, text, paper);
    const char *expected = text;

    ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_writes_capitalized_tex_and_a_space_to_a_paper_with_a_point_durability_of_4)
{
    Pencil pencil;
    char paper[BUFSIZ] = {0};
    unsigned int point_durability = 4;

    pencil_ctor(&pencil, point_durability);

    const char *text = "Text";
    const char *actual = pencil_write_to_paper(&pencil, text, paper);
    const char *expected = "Tex ";

    ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_writes_capitalized_tex_and_a_space_and_newline_to_a_paper_with_a_point_durability_of_4)
{
    Pencil pencil;
    char paper[BUFSIZ] = {0};
    unsigned int point_durability = 4;

    pencil_ctor(&pencil, point_durability);

    const char *text = "Text\n";
    const char *actual = pencil_write_to_paper(&pencil, text, paper);
    const char *expected = "Tex \n";

    ck_assert_str_eq(actual, expected);
}
END_TEST

// Sharpen
START_TEST(test_remembers_the_initial_point_durability_the_pencil_was_initialized_with)
{
    Pencil pencil;
    unsigned int point_durability = 9001;

    pencil_ctor(&pencil, point_durability);

    ck_assert_int_eq(pencil.initial_point_durability, point_durability);
}
END_TEST

START_TEST(test_regains_its_initial_point_durability_when_the_pencil_is_sharpened)
{
    Pencil pencil;
    char paper[BUFSIZ] = {0};
    unsigned int point_durability = 9001;
    const char *text = "Hello world!";

    pencil_ctor(&pencil, point_durability);
    pencil_write_to_paper(&pencil, text, paper);
    pencil_sharpen(&pencil);

    ck_assert_int_eq(pencil.point_durability, point_durability);
}
END_TEST

START_TEST(test_should_create_a_pencil_with_an_initial_length_value)
{
    Pencil pencil;
    unsigned int point_durability = 9001;

    pencil_ctor(&pencil, point_durability);

    ck_assert_int_eq(pencil.length, PENCIL_LENGTH);
}
END_TEST

START_TEST(test_reduces_the_length_of_the_pencil_by_one_each_time_it_is_sharpened)
{
    Pencil pencil;
    unsigned int point_durability = 9001;

    pencil_ctor(&pencil, point_durability);

    unsigned int expected = (pencil.length - 1);

    pencil_sharpen(&pencil);

    unsigned int actual = pencil.length;

    ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_no_longer_sharpens_the_pencil_when_its_length_is_depleted)
{
    Pencil pencil;
    char paper[BUFSIZ] = {0};
    const char *text = "Hello world!";
    unsigned int point_durability = strnlen(text, BUFSIZ);

    pencil_ctor(&pencil, point_durability);

    while (pencil.length > 0) {
        pencil_sharpen(&pencil);
    }

    pencil_write_to_paper(&pencil, text, paper);
    pencil_sharpen(&pencil);

    unsigned int actual = pencil.point_durability;
    unsigned int expected = 0;

    ck_assert_int_eq(actual, expected);
}
END_TEST

// Erase
START_TEST(test_verify_a_sentence_has_a_word_count_of_13)
{
    Pencil pencil;
    char paper[BUFSIZ] = {0};
    unsigned int point_durability = 9001;
    const char *text = "How much wood would a woodchuck chuck if a woodchuck could chuck wood?";

    pencil_ctor(&pencil, point_durability);
    pencil_write_to_paper(&pencil, text, paper);

    size_t actual = paper_word_count(paper);
    size_t expected = 13;

    ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_verify_an_empty_string_has_a_word_count_of_0)
{
    char paper[BUFSIZ] = {0};
    size_t actual = paper_word_count(paper);
    size_t expected = 0;

    ck_assert_int_eq(actual, expected);
}
END_TEST

Suite *kata_suite(void)
{
    Suite *suite = suite_create("Pencil Durability Kata");
    TCase *write_tcase = tcase_create("Write");
    TCase *point_degradation_tcase = tcase_create("Point Degradation");
    TCase *sharpen_tcase = tcase_create("Sharpen");
    TCase *erase_tcase = tcase_create("Erase");

    // Write
    tcase_add_test(write_tcase, test_it_writes_to_paper);
    tcase_add_test(write_tcase, test_should_append_text_to_the_paper);
    suite_add_tcase(suite, write_tcase);

    // Point Degradation
    tcase_add_test(point_degradation_tcase, test_initializes_a_pencil_with_a_point_durability);
    tcase_add_test(point_degradation_tcase, test_expends_no_point_durability_writing_spaces);
    tcase_add_test(point_degradation_tcase, test_expends_no_point_durability_writing_newlines);
    tcase_add_test(point_degradation_tcase, test_expends_one_point_of_durability_writing_a_lowercase_character);
    tcase_add_test(point_degradation_tcase, test_expends_two_points_of_durability_writing_an_uppercase_character);
    tcase_add_test(point_degradation_tcase, test_writes_text_to_a_paper_with_a_point_durability_of_4);
    tcase_add_test(point_degradation_tcase, test_writes_capitalized_tex_and_a_space_to_a_paper_with_a_point_durability_of_4);
    tcase_add_test(point_degradation_tcase, test_writes_capitalized_tex_and_a_space_and_newline_to_a_paper_with_a_point_durability_of_4);
    suite_add_tcase(suite, point_degradation_tcase);

    // Sharpen
    tcase_add_test(sharpen_tcase, test_remembers_the_initial_point_durability_the_pencil_was_initialized_with);
    tcase_add_test(sharpen_tcase, test_regains_its_initial_point_durability_when_the_pencil_is_sharpened);
    tcase_add_test(sharpen_tcase, test_should_create_a_pencil_with_an_initial_length_value);
    tcase_add_test(sharpen_tcase, test_reduces_the_length_of_the_pencil_by_one_each_time_it_is_sharpened);
    tcase_add_test(sharpen_tcase, test_no_longer_sharpens_the_pencil_when_its_length_is_depleted);
    suite_add_tcase(suite, sharpen_tcase);

    // Erase
    tcase_add_test(erase_tcase, test_verify_a_sentence_has_a_word_count_of_13);
    tcase_add_test(erase_tcase, test_verify_an_empty_string_has_a_word_count_of_0);
    suite_add_tcase(suite, erase_tcase);

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
