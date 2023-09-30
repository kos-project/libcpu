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
 * @since 30/09/2023
 */

#pragma once

#include "memory.h"

#define CALL_IF_ENABLED(mask, bit, fn, ...)                                                                            \
    do {                                                                                                               \
        if((mask & bit) == bit) {                                                                                      \
            fn(__VA_ARGS__);                                                                                           \
        }                                                                                                              \
    } while(0)

#define RETURN_IF_MATCH(addr1, addr2, size, ...)                                                                       \
    do {                                                                                                               \
        if(LCPU_MEMCMP(addr1, addr2, size)) {                                                                          \
            return __VA_ARGS__;                                                                                        \
        }                                                                                                              \
    } while(0)

#define SET_BIT_IF(value, bitmask, bit)                                                                                \
    do {                                                                                                               \
        if(value) {                                                                                                    \
            bitmask |= bit;                                                                                            \
        }                                                                                                              \
    } while(0)