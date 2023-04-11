// Copyright (c) 2023 Dominik Marcinowski <dmarcinowski@zoho.com>
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "string_builder.h"

#define SB_MIN_SIZE 32

SB_DEF StringBuilder *sb_create(size_t size)
{
    StringBuilder *sb;

    if (size == 0 || size < SB_MIN_SIZE)
        size = SB_MIN_SIZE;

    sb = (StringBuilder *)malloc(sizeof(*sb));
    sb->data = (char *)malloc(SB_MIN_SIZE);
    *sb->data = '\0';
    sb->size = 0;
    sb->capacity = SB_MIN_SIZE;

    return sb;
}

SB_DEF void sb_free(StringBuilder *sb)
{
    if (sb == NULL) return;
    free(sb->data);
    free(sb);
}

SB_DEF size_t sb_size(StringBuilder *sb)
{
    if (sb == NULL) return 0;
    return sb->size;
}

SB_DEF char *sb_data(StringBuilder *sb)
{
    if (sb == NULL) return NULL;
    return sb->data;
}

SB_DEF const char *sb_dump(StringBuilder *sb)
{
    if (sb == NULL) return NULL;
    char *out = (char *)malloc(sb->size + 1);
    memcpy(out, sb->data, sb->size+1);
    return out;
}

static void sb_ensure_space(StringBuilder *sb, size_t add_size)
{
    if (sb == NULL || add_size == 0) return;
    if (sb->capacity >= sb->size + add_size + 1) return;

    while (sb->capacity < sb->size + add_size + 1) {
        sb->capacity <<= 1;
        if (sb->capacity == 0) {
            sb->capacity--;
        }
    }

    sb->data = (char *)realloc(sb->data, sb->capacity);
}

SB_DEF void sb_append_str(StringBuilder *sb, const char *str, size_t size)
{
    if (sb == NULL || str == NULL || *str == '\0') return;
    if (size == 0) size = strlen(str);

    sb_ensure_space(sb, size);
    memmove(sb->data + sb->size, str, size);

    sb->data += size;
    sb->data[sb->size] = '\0';
}

SB_DEF void sb_append_char(StringBuilder *sb, char c)
{
    if (sb == NULL) return;

    sb_ensure_space(sb, 1);

    sb->data[sb->size] = c;
    sb->size += 1;
    sb->data[sb->size] = '\0';
}

SB_DEF void sb_append_int(StringBuilder *sb, int value)
{
    if (sb == NULL) return;

    char str[12];
    snprintf(str, sizeof(str), "%d", value);
    sb_append_str(sb, str, 0);
}

SB_DEF void sb_append_bool(StringBuilder *sb, bool value)
{
    if (sb == NULL) return;
    if (value == true) {
        sb_append_str(sb, "true", 4);
    } else {
        sb_append_str(sb, "false", 5);
    }
}

SB_DEF void sb_clear(StringBuilder *sb)
{
    if (sb == NULL) return;
    sb_drop_back(sb, sb->size);
}

SB_DEF void sb_drop_front(StringBuilder *sb, size_t count)
{
    if (sb == NULL) return;
    if (count >= sb->size) {
        sb_clear(sb);
        return;
    }

    sb->size -= count;
    memmove(sb->data, sb->data + count, sb->size + 1);
}

SB_DEF void sb_drop_back(StringBuilder *sb, size_t count)
{
    if (sb == NULL) return;
    if (count >= sb->size) return;

    sb->size -= count;
    sb->data[sb->size] = '\0';
}

void sb_trim(StringBuilder *sb)
{
    if (sb == NULL) return;
    sb_trim_back(sb);
    sb_trim_front(sb);
}

void sb_trim_front(StringBuilder *sb)
{
    if (sb == NULL) return;

    size_t i = 0;
    while (i < sb->size && isspace(sb->data[i])) {
        i += 1;
    }
    sb_drop_front(sb, i);
}

void sb_trim_back(StringBuilder *sb)
{
    if (sb == NULL) return;

    size_t i = sb->size;
    while (i < sb->size && isspace(sb->data[sb->size - 1 - i])) {
        i += 1;
    }

    sb_drop_back(sb, i);
}
