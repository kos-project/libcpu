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
 * @since 29/09/2023
 */

#pragma once

#include "cpu/cpu_types.h"

// clang-format off
#define LCPU_MEMSET(addr, value, size)                     \
    do {                                                   \
        cpu_u8* data = (cpu_u8*) addr;                     \
        const cpu_u8 byte_value = (cpu_u8) (value & 0xFF); \
        for(cpu_usize index = 0; index < size; ++index) {  \
            data[index] = byte_value;                      \
        }                                                  \
    } while(0)

#define LCPU_MEMCPY(dst, src, size)                       \
    do {                                                  \
        cpu_u8* dst_ptr = (cpu_u8*)dst;                   \
        const cpu_u8* src_ptr = (const cpu_u8*)src;       \
        for(cpu_usize index = 0; index < size; ++index) { \
            dst_ptr[index] = src_ptr[index];              \
        }                                                 \
    } while(0)

#define LCPU_MEMCMP(addr1, addr2, size) memcmp_impl(addr1, addr2, size)
#define LCPU_ARRAYLEN(array) (sizeof(array) / sizeof(*array))
#define LCPU_STRLEN(address) strlen_impl(address)
// clang-format on

static inline cpu_usize strlen_impl(const char* address) {
    if(address == nullptr) {
        return 0;
    }
    const char* begin = address;
    while(*address != '\0') {
        ++address;
    }
    return ((cpu_usize) address) - ((cpu_usize) begin);
}

static inline cpu_bool memcmp_impl(const void* addr1, const void* addr2, cpu_usize size) {
    const cpu_u8* data1 = (const cpu_u8*) addr1;
    const cpu_u8* data2 = (const cpu_u8*) addr2;
    for(cpu_usize index = 0; index < size; ++index) {
        if(data1[index] == data2[index]) {
            continue;
        }
        return LCPU_FALSE;
    }
    return LCPU_TRUE;
}