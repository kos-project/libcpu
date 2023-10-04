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
 * @since 04/10/2023
 */

#ifdef CPU_ARM

#include "cpu/cpu.h"

// NOLINTBEGIN
// clang-format off
static CPUFeature g_available_features[] = {
};
// clang-format on
static CPUFeature g_enabled_features = CPU_FEATURE_NONE;
static cpu_bool g_is_initialized = LCPU_FALSE;
static cpu_bool g_is_usermode = LCPU_FALSE;
// NOLINTEND

cpu_usize cpu_get_gpr_width() {
#ifdef CPU_64_BIT
    return 64;
#else
    return 32;
#endif
}

cpu_usize cpu_get_vr_width() {
    return cpu_get_gpr_width();// TODO: properly implement this
}

CPUVendor cpu_get_vendor() {
    return CPU_VENDOR_UNKNOWN;
}

const char* cpu_vendor_get_name(CPUVendor vendor) {
    return "Unknown";
}

CPUFeature cpu_get_features() {
    return CPU_FEATURE_NONE;
}

CPUFeature cpu_get_enabled_features() {
    return CPU_FEATURE_NONE;
}

const CPUFeature* cpu_get_available_features() {
    return g_available_features;
}

cpu_usize cpu_get_num_available_features() {
    return LCPU_ARRAYLEN(g_available_features);
}

const char* cpu_feature_get_name(CPUFeature feature) {
    return "Unknown";
}

void cpu_reset_state() {
    g_is_initialized = LCPU_FALSE;
}

void cpu_init(CPUFeature features) {
    if(g_is_initialized) {
        return;
    }
    g_enabled_features = features;
    g_is_initialized = LCPU_TRUE;
}

cpu_bool cpu_is_initialized() {
    return g_is_initialized;
}

void cpu_set_exception_handler(CPUExceptionHandler handler) {
    g_exception_handler = handler;
}

CPUExceptionHandler cpu_get_exception_handler() {
    return g_exception_handler;
}

void cpu_hint_spin() {
    // TODO: implement this
}

_Noreturn void cpu_halt() {
    // TODO: implement this
}

void cpu_enter_usermode() {
    g_is_usermode = LCPU_TRUE;
}

cpu_bool cpu_is_usermode() {
    return g_is_usermode;
}

cpu_usize cpu_popcnt16(cpu_u16 value) {
    cpu_usize count = 0;
    while(value != 0) {
        value &= (value - 1);
        ++count;
    }
    return count;
}

cpu_usize cpu_popcnt32(cpu_u32 value) {
    cpu_usize count = 0;
    while(value != 0) {
        value &= (value - 1);
        ++count;
    }
    return count;
}

cpu_usize cpu_popcnt64(cpu_u64 value) {
    cpu_usize count = 0;
    while(value != 0) {
        value &= (value - 1);
        ++count;
    }
    return count;
}

#endif