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

#ifndef SV_H_
#define SV_H_

#include <stdbool.h>
#include <stddef.h>

#ifndef SV_DEF
#define SV_DEF
#endif // SV_DEF

typedef struct {
    const char *data;
    size_t      size;
} StringView;

// StringView literal operators.
#define SV(cstr_literal) sv_from_parts(cstr_literal, sizeof(cstr_literal) - 1)
#define SV_NULL sv_from_parts(NULL, 0)
#define SV_STATIC(cstr_literal)   \
    {                             \
        sizeof(cstr_literal) - 1, \
        (cstr_literal)            \
    }

// Printf macros for StringView. Example:
//   StringView name = ...;
//   printf("Name: "SV_Fmt"\n", SV_Arg(name));
#define SV_Fmt "%.*s"
#define SV_Arg(sv) (int) (sv).size, (sv).data

SV_DEF StringView  sv_from_parts(const char *data, size_t sz);
SV_DEF StringView  sv_from_cstr(const char *cstr);
SV_DEF StringView  sv_substr(StringView *sv, size_t start, size_t end);

SV_DEF char        sv_at(StringView *sv, size_t pos);
SV_DEF char        sv_front(StringView *sv);
SV_DEF char        sv_back(StringView *sv);
SV_DEF size_t      sv_size(StringView *sv);
SV_DEF const char *sv_data(StringView *sv);
              

SV_DEF bool        sv_equal(StringView *a, StringView *b);
SV_DEF bool        sv_equal_ignorecase(StringView *a, StringView *b);
SV_DEF bool        sv_contains_char(StringView *sv, char c, size_t *idx);
SV_DEF bool        sv_starts_with(StringView *sv, StringView prefix);
SV_DEF bool        sv_ends_with(StringView *sv, StringView suffix);

SV_DEF void        sv_trim(StringView *sv);
SV_DEF void        sv_trim_front(StringView *sv);
SV_DEF void        sv_trim_back(StringView *sv);
SV_DEF void        sv_drop_front(StringView *sv, size_t count);
SV_DEF void        sv_drop_back(StringView *sv, size_t count);
SV_DEF StringView  sv_chop_front(StringView *sv, size_t count);
SV_DEF StringView  sv_chop_back(StringView *sv, size_t count);
SV_DEF StringView  sv_chop_by_delim(StringView *sv, char delim);
SV_DEF StringView  sv_chop_by_sv(StringView *sv, StringView delim);

#endif // SV_H_
