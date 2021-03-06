#ifndef PENCIL_H
#define PENCIL_H

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "kata.h"

#define PENCIL_LENGTH (5)

typedef struct {
    unsigned int initial_point_durability;
    unsigned int length;
    unsigned int point_durability;
} Pencil;

void pencil_ctor(Pencil *pencil, unsigned int point_durability)
{
    pencil->initial_point_durability = point_durability;
    pencil->length = PENCIL_LENGTH;
    pencil->point_durability = point_durability;
}

unsigned int pencil_degradation(char character)
{
    // Whitespace doesn't degrade the pencil tip.
    if (character == KATA_NEWLINE || character == KATA_SPACE) {
        return 0;
    }

    // Lowercase letters degrade by a single point.
    if (character == tolower(character)) {
        return 1;
    }

    // Uppercase letters degrade by two points.
    return 2;
}

unsigned int pencil_sharpen(Pencil *pencil)
{
    // If there is no remaining pencil length we do NOT sharpen.
    if (pencil->length == 0) {
        return pencil->point_durability;
    }

    pencil->length -= 1;
    pencil->point_durability = pencil->initial_point_durability;

    return pencil->point_durability;
}

unsigned int pencil_str_degradation(const char *text)
{
    unsigned int degradation = 0;
    size_t text_length = strnlen(text, BUFSIZ);
    char character;

    for (size_t pos = 0; pos < text_length; ++pos) {
        character = text[pos];
        degradation += pencil_degradation(character);
    }

    return degradation;
}

char * pencil_write_to_paper(Pencil *pencil, const char *text, char *restrict paper)
{
    size_t text_length = strnlen(text, BUFSIZ);

    assert(text_length < BUFSIZ);

    char text_buffer[BUFSIZ] = {0};
    char character;
    unsigned int degradation;
    size_t pos;

    for (pos = 0; pos < text_length; ++pos) {
        character = text[pos];
        degradation = pencil_degradation(character);

        // Write the character if we have enough point durability.
        if (pencil->point_durability >= degradation) {
            pencil->point_durability -= degradation;
            text_buffer[pos] = text[pos];
            continue;
        }

        // Write a space if we don't have enough point durability.
        text_buffer[pos] = ' ';
    }

    text_buffer[pos] = '\0';

    return strncat(paper, text_buffer, BUFSIZ);
}

#endif // PENCIL_H
