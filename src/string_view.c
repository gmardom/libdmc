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

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "string_view.h"

SV_DEF StringView sv_from_parts(const char *data, size_t sz)
{
    StringView sv;
    sv.size = sz;
    sv.data = data;
    return sv;
}

SV_DEF StringView sv_from_cstr(const char *cstr)
{
    return sv_from_parts(cstr, strlen(cstr));
}

SV_DEF StringView sv_substr(StringView *sv, size_t start, size_t end)
{
    if (sv == NULL) return SV_NULL;
    if (end > sv->size) end = sv->size-1;
    if (start > end) return SV_NULL;
    return sv_from_parts(sv->data + start, sv->size - end);
}

SV_DEF char sv_at(StringView *sv, size_t pos)
{
    if (sv == NULL) return '\0';
    if (pos >= sv->size) return '\0';
    return sv->data[pos];
}

SV_DEF char sv_front(StringView *sv)
{
    return sv_at(sv, 0);
}

SV_DEF char sv_back(StringView *sv)
{
    return sv_at(sv, sv->size-1);
}

SV_DEF size_t sv_size(StringView *sv)
{
    if (sv == NULL) return 0;
    return sv->size;
}

SV_DEF const char *sv_data(StringView *sv)
{
    if (sv == NULL) return NULL;
    return sv->data;
}

SV_DEF bool sv_equal(StringView *a, StringView *b)
{
    if (a == NULL || b == NULL) return false;
    if (a->size   !=   b->size) return false;
    return memcmp(a->data, b->data, a->size) == 0;
}

SV_DEF bool sv_equal_ignorecase(StringView *a, StringView *b)
{
    if (a == NULL || b == NULL) return false;
    if (a->size   !=   b->size) return false;

    char x, y;
    for (size_t i = 0; i < a->size; ++i) {
        x = 'A' <= a->data[i] && a->data[i] <= 'Z'
            ? a->data[i] + 32
            : a->data[i];
        y = 'A' <= b->data[i] && b->data[i] <= 'Z'
            ? b->data[i] + 32
            : b->data[i];

        if (x != y) return false;
    }

    return true;
}

SV_DEF bool sv_contains(StringView *sv, char c, size_t *idx)
{
    if (sv == NULL) return false;

    size_t i = 0;
    while (i < sv->size && sv->data[i] != c) {
        i += 1;
    }

    if (i < sv->size) {
        if (idx != NULL) {
            *idx = i;
        }
        return true;
    }

    return false;
}

SV_DEF bool sv_starts_with(StringView *sv, StringView prefix)
{
    if (sv == NULL) return false;

    if (prefix.size <= sv->size) {
        StringView actual = sv_from_parts(sv->data, prefix.size);
        return sv_equal(&prefix, &actual);
    }

    return false;
}

SV_DEF bool sv_ends_with(StringView *sv, StringView suffix)
{
    if (sv == NULL) return false;

    if (suffix.size <= sv->size) {
        StringView actual = sv_from_parts(sv->data + sv->size - suffix.size, suffix.size);
        return sv_equal(&suffix, &actual);
    }

    return false;
}

SV_DEF void sv_trim(StringView *sv)
{
    if (sv == NULL) return;
    sv_trim_back(sv);
    sv_trim_front(sv);
}

SV_DEF void sv_trim_front(StringView *sv)
{
    if (sv == NULL) return;

    size_t i = 0;
    while (i < sv->size && isspace(sv->data[sv->size-1-i])) {
        i += 1;
    }

    sv_drop_front(sv, i);
}

SV_DEF void sv_trim_back(StringView *sv)
{
    if (sv == NULL) return;

    size_t i = 0;
    while (i < sv->size && isspace(sv->data[i])) {
        i += 1;
    }

    sv_drop_back(sv, i);
}

SV_DEF void sv_drop_front(StringView *sv, size_t count)
{
    if (sv == NULL || count == 0) return;
    if (count >= sv->size) {
        sv_drop_back(sv, sv->size-1);
        return;
    }

    sv->size -= count;
    sv->data += count;
}

SV_DEF void sv_drop_back(StringView *sv, size_t count)
{
    if (sv == NULL || count == 0) return;
    if (count > sv->size) {
        count = sv->size;
    }

    sv->size -= count;
}

SV_DEF StringView sv_chop_front(StringView *sv, size_t count)
{
    if (sv == NULL || count == 0) return SV_NULL;
    if (count > sv->size) {
        count = sv->size;
    }

    StringView res = sv_from_parts(sv->data, count);

    sv->size -= count;
    sv->data += count;

    return res;
}

SV_DEF StringView sv_chop_back(StringView *sv, size_t count)
{
    if (sv == NULL || count == 0) return SV_NULL;
    if (count > sv->size) {
        count = sv->size;
    }

    StringView res = sv_from_parts(sv->data + sv->size - count, count);

    sv->size -= count;

    return res;
}

SV_DEF StringView sv_chop_by_delim(StringView *sv, char delim)
{
    if (sv == NULL) return SV_NULL;

    size_t i = 0;
    while (i < sv->size && sv->data[i] != delim) {
        i += 1;
    }

    return sv_chop_front(sv, i < sv->size ? i+1 : i);
}

SV_DEF StringView sv_chop_by_sv(StringView *sv, StringView delim)
{
    if (sv == NULL) return SV_NULL;

    StringView window = sv_from_parts(sv->data, delim.size);

    size_t i = 0;
    while (i+delim.size < sv->size && !(sv_equal(&window, &delim))) {
        i++;
        window.data++;
    }

    StringView res = sv_from_parts(sv->data, i);
    if (i+delim.size == sv->size) {
        res.size += delim.size;
    }

    sv_drop_front(sv, i+delim.size);
    return res;
}
