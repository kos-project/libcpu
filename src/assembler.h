// Copyright 2023 Karma Krafts & associates
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * A simple collection of macros that make up a GAS macro assembler
 * for easily writing readable inline assembly code
 *
 * @author Alexander Hinze
 * @since 16/09/2023
 */

#pragma once

#include "cpu/cpu_types.h"

// clang-format off
#define _str(x...) #x
#define _strx(...) _str(__VA_ARGS__)

#define _ins(...) __VA_ARGS__
#define _in(n) [n]"r"(n)
#define _named_in(n, v) [n]"r"(v)
#define _outs(...) __VA_ARGS__
#define _out(n) [n]"=r"(n)
#define _named_out(n, v) [n]"=r"(v)
#define _inout(n) [n]"+r"(n)
#define _named_inout(n, v) [n]"+r"(v)

#define _emitI(...) _strx(__VA_ARGS__) ";"
#define _emitL(n) #n ":;"
#define _reg(n) %%n
#define _deref(n) *_reg(n)
#define _var(n) %[n]
#define _get(x, ...) __VA_ARGS__(x)
#define _imm(x) $##x

#define _clobs(...) __VA_ARGS__
#define _clobx(n) #n
#define _clob(n) _clobx(n)
// clang-format on

#ifdef CPU_X86
#ifdef CPU_64_BIT
#define _sized(n) r##n
#else
#define _sized(n) e##n
#endif
#else
#error Unsupported CPU architecture
#endif

#define _sreg(n) _reg(_sized(n))
#define _sclob(n) _clob(_sized(n))

// clang-format off
#define _assemble(ins, outs, clobs, ...) \
__asm__ __volatile__(                    \
    __VA_ARGS__                          \
    : outs                               \
    : ins                                \
    : clobs                              \
)
// clang-format on