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
 * @author Alexander Hinze
 * @since 23/09/2023
 */

#pragma once

// Compiler-dependant modifier for preventing a specific function from being optimized
#if defined(COMPILER_GCC)
#define LCPU_NOOPT __attribute__((optimize("0")))
#elif defined(COMPILER_CLANG)
#define LCPU_NOOPT __attribute__((optnone))
#else
#error Unsupported compiler
#endif

#ifdef __cplusplus
#define LCPU_API_BEGIN extern "C" {
#define LCPU_API_END }
#define LCPU_STATIC_ASSERT(x, m) static_assert(x, m)
#else//__cplusplus
#define LCPU_API_BEGIN
#define LCPU_API_END
#define LCPU_STATIC_ASSERT(x, m) _Static_assert(x, m)
#endif//__cplusplus

#ifdef CPU_64_BIT
#define LCPU_GPR_BITS 64
#else
#define LCPU_GPR_BITS 32
#endif

#define LCPU_GPR_BYTES (LCPU_GPR_BITS >> 3)