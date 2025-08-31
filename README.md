# sb
A C89 standard compliant, single header, nostdlib (no C Standard Library) String Builder (SB).

For more information please look at the "sb.h" file or take a look at the "examples" or "tests" folder.

> [!WARNING]
> THIS PROJECT IS A WORK IN PROGRESS! ANYTHING CAN CHANGE AT ANY MOMENT WITHOUT ANY NOTICE! USE THIS PROJECT AT YOUR OWN RISK!

<p align="center">
  <a href="https://github.com/nickscha/sb/releases">
    <img src="https://img.shields.io/github/v/release/nickscha/sb?style=flat-square&color=blue" alt="Latest Release">
  </a>
  <a href="https://github.com/nickscha/sb/releases">
    <img src="https://img.shields.io/github/downloads/nickscha/sb/total?style=flat-square&color=brightgreen" alt="Downloads">
  </a>
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square" alt="License">
  </a>
  <img src="https://img.shields.io/badge/Standard-C89-orange?style=flat-square" alt="C Standard">
  <img src="https://img.shields.io/badge/nolib-nostdlib-lightgrey?style=flat-square" alt="nostdlib">
</p>

## **Features**
- **C89 compliant** — portable and legacy-friendly  
- **Single-header API** — just include `sb.h`  
- **nostdlib** — no dependency on the C Standard Library  
- **Minimal binary size** — optimized for small executables  
- **Cross-platform** — Works on all Platforms
- **Strict compilation** — built with aggressive warnings & safety checks  

## Quick Start

Download or clone sb.h and include it in your project.

```C
#include "sb.h" /* String Builder */

int main(void) {

    /* Initialize the string builder */
    char buf[256];
    sb sb;
    sb_init(&sb, buf, sizeof(buf));

    /* Examples for formatting numbers */
    sb_append_cstr(&sb, "  none: '");
    sb_append_long(&sb, 123, 8, SB_PAD_NONE);
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

    /* Add terminator to string builder */
    sb_term(&sb);

    /* Afterwards you can print the "sb.buf" or "buf" directly */

    return 0;
}
```

Output will be:

```txt
  none: '123'
  left: '123     '
 right: '     123'
double: '  -3.1416'
 float: '   0.1234'
```

## Run Example: nostdlib, freestsanding

In this repo you will find the "examples/sb_win32_nostdlib.c" with the corresponding "build.bat" file which
creates an executable only linked to "kernel32" and is not using the C standard library and executes the program afterwards.

## "nostdlib" Motivation & Purpose

nostdlib is a lightweight, minimalistic approach to C development that removes dependencies on the standard library. The motivation behind this project is to provide developers with greater control over their code by eliminating unnecessary overhead, reducing binary size, and enabling deployment in resource-constrained environments.

Many modern development environments rely heavily on the standard library, which, while convenient, introduces unnecessary bloat, security risks, and unpredictable dependencies. nostdlib aims to give developers fine-grained control over memory management, execution flow, and system calls by working directly with the underlying platform.

### Benefits

#### Minimal overhead
By removing the standard library, nostdlib significantly reduces runtime overhead, allowing for faster execution and smaller binary sizes.

#### Increased security
Standard libraries often include unnecessary functions that increase the attack surface of an application. nostdlib mitigates security risks by removing unused and potentially vulnerable components.

#### Reduced binary size
Without linking to the standard library, binaries are smaller, making them ideal for embedded systems, bootloaders, and operating systems where storage is limited.

#### Enhanced performance
Direct control over system calls and memory management leads to performance gains by eliminating abstraction layers imposed by standard libraries.

#### Better portability
By relying only on fundamental system interfaces, nostdlib allows for easier porting across different platforms without worrying about standard library availability.
