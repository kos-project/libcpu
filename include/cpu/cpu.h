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

#include "cpu_api.h"
#include "cpu_types.h"

#pragma once

LCPU_API_BEGIN

typedef enum _CPUFeature : cpu_u32 {// clang-format off
    CPU_FEATURE_NONE        = 0,
    CPU_FEATURE_X87         = 1,
    CPU_FEATURE_MMX         = 1 << 1,
    CPU_FEATURE_SSE         = 1 << 2,
    CPU_FEATURE_SSE2        = 1 << 3,
    CPU_FEATURE_SSE3        = 1 << 4,
    CPU_FEATURE_SSSE3       = 1 << 5,
    CPU_FEATURE_SSE4_1      = 1 << 6,
    CPU_FEATURE_SSE4_2      = 1 << 7,
    CPU_FEATURE_SSE4A       = 1 << 8,
    CPU_FEATURE_AVX         = 1 << 9,
    CPU_FEATURE_AVX2        = 1 << 10,
    CPU_FEATURE_AVX512      = 1 << 11,
    CPU_FEATURE_FMA3        = 1 << 12,
    CPU_FEATURE_FMA4        = 1 << 13,
    CPU_FEATURE_XSAVE       = 1 << 14,
    CPU_FEATURE_OSXSAVE     = 1 << 15,
    CPU_FEATURE_FXSR        = 1 << 16,
    CPU_FEATURE_NX          = 1 << 17,
    CPU_FEATURE_RDRND       = 1 << 18,
    CPU_FEATURE_RDTSC       = 1 << 19,
    CPU_FEATURE_CX8         = 1 << 20,
    CPU_FEATURE_CX16        = 1 << 21,
    CPU_FEATURE_MONITOR     = 1 << 22,
    CPU_FEATURE_POPCNT      = 1 << 23,
    CPU_FEATURE_NEON        = 1 << 24,
    CPU_FEATURE_RVV         = 1 << 25
} CPUFeature; // clang-format off

typedef enum _CPUVendor {
    CPU_VENDOR_UNKNOWN,
    CPU_VENDOR_AMD,
    CPU_VENDOR_INTEL,
    CPU_VENDOR_CYRIX,
    CPU_VENDOR_TRANSMETA,
    CPU_VENDOR_VIA,
    CPU_VENDOR_SIS,
    CPU_VENDOR_UMC,
    CPU_VENDOR_RISE,
    CPU_VENDOR_NEXGEN,
    CPU_VENDOR_NSC,
    // Virtual CPU vendors (software ID)
    CPU_VENDOR_KVM,
    CPU_VENDOR_QEMU,
    CPU_VENDOR_HYPERV,
    CPU_VENDOR_PARALLELS,
    CPU_VENDOR_VMWARE,
    CPU_VENDOR_XENHVM,
    CPU_VENDOR_ACRN,
    CPU_VENDOR_QNX,
    CPU_VENDOR_ROSETTA,
    CPU_VENDOR_BHYVE,
    CPU_VENDOR_MSXTA
} CPUVendor;

typedef enum _CPUException {
    CPU_EXCEPTION_NONE,
    CPU_EXCEPTION_PAGE_FAULT
} CPUException;

/**
 * A function pointer type for passing around exception handler callbacks.
 */
typedef void(*CPUExceptionHandler)(CPUException exception);

/**
 * @return The maximum number of bits a general purpose register can fit.
 *  Usually something like 32 or 64.
 */
cpu_usize cpu_get_gpr_width();

/**
 * @return The maximum number of bits a vector register can fit.
 *  Usually between 128 and 512 bits.
 */
cpu_usize cpu_get_vr_width();

/**
 * @return The vendor of the current processor.
 */
CPUVendor cpu_get_vendor();

/**
 * Convert the given vendor type to a null-terminated string.
 * @param vendor The vendor type to convert.
 * @return A null-terminated string representation of the given vendor type.
 */
const char* cpu_vendor_get_name(CPUVendor vendor);

/**
 * @return A bitmask of features available on the current processor.
 */
CPUFeature cpu_get_features();

/**
 * @return A bitmask of features currently enabled on the current processor.
 */
CPUFeature cpu_get_enabled_features();

/**
 * @return An array of all available CPU features on the current architecture.
 *  Used in conjunction with cpu_get_num_available_features().
 */
const CPUFeature* cpu_get_available_features();

/**
 * @return The number of all available features on the current architecture.
 *  Used in conjunction with cpu_get_available_features().
 */
cpu_usize cpu_get_num_available_features();

/**
 * Convert the given feature bit to a null-terminated string.
 * @param feature The feature bit to convert.
 * @return A null-terminated string representation of the given feature bit.
 */
const char* cpu_feature_get_name(CPUFeature feature);

/**
 * Resets the internal state of the current processor.
 * This can be used after transitioning from firmware to kernel for example.
 */
void cpu_reset_state();

/**
 * Initialize the current processor with the given features.
 * For enabling all features, a call to cpu_get_features()
 * should be passed in.
 * @param features A bitmask of features to enable on the current processor.
 */
void cpu_init(CPUFeature features);

/**
 * @return True if the CPU has already been initialized.
 */
cpu_bool cpu_is_initialized();

/**
 * Set the exception handler callback for the current processor.
 * The given function will be called from all relevant interrupt service routines.
 * @param handler A function to handle the given exception.
 */
void cpu_set_exception_handler(CPUExceptionHandler handler);

/**
 * @return The exception handler callback of the current processor.
 */
CPUExceptionHandler cpu_get_exception_handler();

/**
 * Gives the current processor a hint that it is in a spin-loop.
 * This prevents the processor being pinned at 100% and greatly
 * reduces energy consumption.
 */
void cpu_hint_spin();

/**
 * Halts the current processor in an infinite loop.
 * This functions does not return.
 */
_Noreturn void cpu_halt();

/**
 * Enters userland code execution on the current processor.
 * This should ideally be called after initializing a kernel
 * when control can be passed to a userland application since
 * it can only be done once.
 */
void cpu_enter_userland();

/**
 * Determines whether the current processor is operating in userland.
 * This function will always return true after cpu_enter_userland() was called.
 * @return True if the current processor is operating in userland.
 */
cpu_bool cpu_is_userland();

/**
 * Count the number of 1-bits in the given value.
 * Hardware accelerated on supported platforms.
 * @param value The value to count 1-bits in.
 * @return The number of set 1-bits in the given value.
 */
cpu_usize cpu_popcnt16(cpu_u16 value);

/**
 * Count the number of 1-bits in the given value.
 * Hardware accelerated on supported platforms.
 * @param value The value to count 1-bits in.
 * @return The number of set 1-bits in the given value.
 */
cpu_usize cpu_popcnt32(cpu_u32 value);

/**
 * Count the number of 1-bits in the given value.
 * Hardware accelerated on supported platforms.
 * @param value The value to count 1-bits in.
 * @return The number of set 1-bits in the given value.
 */
cpu_usize cpu_popcnt64(cpu_u64 value);

LCPU_API_END