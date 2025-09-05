/* sb.h - v0.3 - public domain data structures - nickscha 2025

A C89 standard compliant, single header, nostdlib (no C Standard Library) String Builder (SB).

This Test class defines cases to verify that we don't break the excepted behaviours in the future upon changes.

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

*/
#include "../sb.h"        /* String Builder             */
#include "../deps/test.h" /* Simple Testing framework    */
#include "../deps/perf.h" /* Simple Performance profiler */

void sb_test_init_term(void)
{
  char buf[32];
  sb s;
  sb_init(&s, buf, sizeof(buf));
  assert(s.len == 0);
  assert(s.ovr == 0);
  assert(buf[0] == '\0');

  sb_term(&s);
  assert(buf[s.len] == '\0');
}

void sb_test_putc_append_bytes(void)
{
  char buf[32];
  sb s;
  sb_init(&s, buf, sizeof(buf));

  sb_putc(&s, 'A');
  assert(s.len == 1 && buf[0] == 'A');

  sb_append_bytes(&s, "BC", 2);
  assert(s.len == 3 && sb_ncmp(&s, "ABC", 3) == 0);

  sb_term(&s);
  assert(buf[s.len] == '\0');
}

void sb_test_append_cstr(void)
{
  char buf[32];
  sb s;
  sb_init(&s, buf, sizeof(buf));

  sb_append_cstr(&s, "Hello");
  assert(sb_cmp(&s, "Hello") == 0);

  sb_term(&s);
  assert(buf[s.len] == '\0');
}

void sb_test_append_spaces(void)
{
  char buf[32];
  sb s;
  sb_init(&s, buf, sizeof(buf));

  sb_append_cstr(&s, "A");
  sb_append_spaces(&s, 5);
  sb_append_cstr(&s, "B");
  assert(sb_ncmp(&s, "A     B", 7) == 0);

  sb_term(&s);
  assert(buf[s.len] == '\0');
}

void sb_test_append_ulong_long(void)
{
  char buf[32];
  sb s;
  sb_init(&s, buf, sizeof(buf));

  sb_append_ulong(&s, 12345, 0, SB_PAD_NONE);
  assert(sb_cmp(&s, "12345") == 0);

  s.len = 0;
  sb_append_ulong(&s, 123, 5, SB_PAD_LEFT);
  assert(sb_cmp(&s, "  123") == 0);

  s.len = 0;
  sb_append_long(&s, -42, 5, SB_PAD_RIGHT);
  assert(sb_cmp(&s, "-42  ") == 0);

  sb_term(&s);
  assert(buf[s.len] == '\0');
}

void sb_test_append_double_float(void)
{
  char buf[64];
  sb s;
  sb_init(&s, buf, sizeof(buf));

  sb_append_double(&s, 3.1415, 0, 4, SB_PAD_NONE);
  assert(sb_cmp(&s, "3.1415") == 0);

  s.len = 0;
  sb_append_double(&s, -2.5, 6, 2, SB_PAD_LEFT);
  assert(sb_cmp(&s, " -2.50") == 0);

  s.len = 0;
  sb_append_float(&s, 0.007f, 6, 3, SB_PAD_RIGHT);
  assert(sb_cmp(&s, "0.007 ") == 0);

  sb_term(&s);
  assert(buf[s.len] == '\0');
}

void sb_test_padding_and_format(void)
{
  char buf[256];
  sb sb;
  sb_init(&sb, buf, sizeof(buf));

  sb_append_cstr(&sb, "  none: '");
  sb_append_long(&sb, 123, 8, SB_PAD_NONE);
  sb_append_cstr(&sb, "'\n");

  sb_append_cstr(&sb, " ulong: '");
  sb_append_ulong(&sb, 400, 8, SB_PAD_NONE);
  sb_append_cstr(&sb, "'\n");

  sb_append_cstr(&sb, "  left: '");
  sb_append_long(&sb, 123, 8, SB_PAD_RIGHT);
  sb_append_cstr(&sb, "'\n");

  sb_append_cstr(&sb, " right: '");
  sb_append_long(&sb, 123, 8, SB_PAD_LEFT);
  sb_append_cstr(&sb, "'\n");

  sb_append_cstr(&sb, "double: '");
  sb_append_double(&sb, -3.14159, 9, 4, SB_PAD_LEFT);
  sb_append_cstr(&sb, "'\n");

  sb_append_cstr(&sb, " float: '");
  sb_append_float(&sb, 0.1234f, 9, 4, SB_PAD_LEFT);
  sb_append_cstr(&sb, "'\n");

  sb_term(&sb);

  test_print_string(sb.buf);
}
void sb_test_printf(void)
{
  long score = 42;
  double pi = 3.14159;

  char buf[256];
  sb s;
  sb_init(&s, buf, sizeof(buf));
  sb_printf3(&s, "\"Name: %10s Score: %10d PI: %20.4f\"\n", "Foo", (char *)&score, (char *)&pi);
  sb_term(&s);

  test_print_string(s.buf);
  assert(sb_cmp(&s, "\"Name: Foo        Score: 42         PI: 3.1416              \"\n") == 0);

  sb_init(&s, buf, sizeof(buf));
  sb_printf3(&s, "\"Name: %-10s Score: %-10d PI: %-20.4f\"\n", "Foo", (char *)&score, (char *)&pi);
  sb_term(&s);

  assert(sb_cmp(&s, "\"Name:        Foo Score:         42 PI:               3.1416\"\n") == 0);

  sb_init(&s, buf, sizeof(buf));
  sb_printf3(&s, "\"Name: %-10s Score: %-10d PI: %-.4f\"\n", "Foo", (char *)&score, (char *)&pi);
  sb_term(&s);

  assert(sb_cmp(&s, "\"Name:        Foo Score:         42 PI: 3.1416\"\n") == 0);
}

int main(void)
{
  sb_test_init_term();
  sb_test_putc_append_bytes();
  sb_test_append_cstr();
  sb_test_append_spaces();
  sb_test_append_ulong_long();
  sb_test_append_double_float();
  sb_test_padding_and_format();
  sb_test_printf();

  test_print_string("[sb] passed all tests");

  return 0;
}

/*
   -----------------------------------------------------------------------------
   This software is available under 2 licenses -- choose whichever you prefer.
   ------------------------------------------------------------------------------
   ALTERNATIVE A - MIT License
   Copyright (c) 2025 nickscha
   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is furnished to do
   so, subject to the following conditions:
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
   ------------------------------------------------------------------------------
   ALTERNATIVE B - Public Domain (www.unlicense.org)
   This is free and unencumbered software released into the public domain.
   Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
   software, either in source code form or as a compiled binary, for any purpose,
   commercial or non-commercial, and by any means.
   In jurisdictions that recognize copyright laws, the author or authors of this
   software dedicate any and all copyright interest in the software to the public
   domain. We make this dedication for the benefit of the public at large and to
   the detriment of our heirs and successors. We intend this dedication to be an
   overt act of relinquishment in perpetuity of all present and future rights to
   this software under copyright law.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
   ------------------------------------------------------------------------------
*/
