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

#ifndef STRING_BUILDER_H_
#define STRING_BUILDER_H_

#include <stdbool.h>
#include <stddef.h>

#ifndef SB_DEF
#define SB_DEF
#endif

typedef struct {
    char    *data;
    size_t   size;
    size_t   capacity;
} StringBuilder;

SB_DEF StringBuilder *sb_create(size_t size);
SB_DEF void           sb_free(StringBuilder *sb);

SB_DEF size_t         sb_size(StringBuilder *sb);
SB_DEF char          *sb_data(StringBuilder *sb);
SB_DEF const char    *sb_dump(StringBuilder *sb);

SB_DEF void           sb_append_str(StringBuilder *sb, const char *str, size_t size);
SB_DEF void           sb_append_char(StringBuilder *sb, char c);
SB_DEF void           sb_append_int(StringBuilder *sb, int value);
SB_DEF void           sb_append_bool(StringBuilder *sb, bool value);
// SB_DEF void           sb_insert_str(StringBuilder *sb, size_t pos, const char *s, size_t len);
// SB_DEF void           sb_insert_char(StringBuilder *sb, size_t pos, char c);
// SB_DEF void           sb_insert_int(StringBuilder *sb, size_t pos, int val);
// SB_DEF void           sb_insert_bool(StringBuilder *sb, size_t pos, int val);

// SB_DEF void           sb_replace_str(StringBuilder *sb, size_t, pos, size_t cnt, const char *s, size_t len);
// SB_DEF void           sb_replace_char(StringBuilder *sb, size_t, pos, size_t cnt, char c);
// SB_DEF void           sb_replace_int(StringBuilder *sb, size_t, pos, size_t cnt, int val);

SB_DEF void           sb_clear(StringBuilder *sb);
SB_DEF void           sb_drop_front(StringBuilder *sb, size_t count);
SB_DEF void           sb_drop_back(StringBuilder *sb, size_t count);
SB_DEF void           sb_trim(StringBuilder *sb);
SB_DEF void           sb_trim_front(StringBuilder *sb);
SB_DEF void           sb_trim_back(StringBuilder *sb);
// SB_DEF void           sb_remove(StringBuilder *sb, size_t pos, size_t cnt);

#endif // STRING_BUILDER_H_
