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

typedef enum _CPUFeature {// clang-format off
    CPU_FEATURE_NONE        = 0,        // No features
    CPU_FEATURE_X87         = 1 << 0,   // [x86/amd64 only] Required for SSSE3+ and AVX+
    CPU_FEATURE_MMX         = 1 << 2,   // [x86/amd64 only] Legacy 64-Bit SIMD extensions
    CPU_FEATURE_SSE         = 1 << 3,   // [x86/amd64 only] SSE
    CPU_FEATURE_SSE2        = 1 << 4,   // [x86/amd64 only] SSE2
    CPU_FEATURE_SSE3        = 1 << 5,   // [x86/amd64 only] SSE2
    CPU_FEATURE_SSSE3       = 1 << 6,   // [amd64 only] SSSE3 (includes SSE3)
    CPU_FEATURE_SSE4_1      = 1 << 7,   // [amd64 only] SSE4.1
    CPU_FEATURE_SSE4_2      = 1 << 8,   // [amd64 only] SSE4.2
    CPU_FEATURE_SSE4A       = 1 << 9,   // [amd64 only] SSE4A
    CPU_FEATURE_AVX         = 1 << 10,  // [amd64 only] AVX
    CPU_FEATURE_AVX2        = 1 << 11,  // [amd64 only] AVX2
    CPU_FEATURE_AVX512      = 1 << 12,  // [amd64 only] AVX512-F
    CPU_FEATURE_FMA3        = 1 << 13,  // [amd64 only] FMA3
    CPU_FEATURE_FMA4        = 1 << 14,  // [amd64 only] FMA4
    CPU_FEATURE_XSAVE       = 1 << 15,  // [x86/amd64 only] XSAVE/XRSTOR/XSETBV/XGETBV instructions
    CPU_FEATURE_OSXSAVE     = 1 << 16,  // [x86/amd64 only] XSAVE in Ring 3
    CPU_FEATURE_FXSR        = 1 << 17,  // [x86/amd64 only] FXSAVE/FXRSTOR instructions
    CPU_FEATURE_NXE         = 1 << 18,  // [x86/amd64/IA64 only] No-execute-enable
    CPU_FEATURE_RDRND       = 1 << 19,  // [x86/amd64 only] On-chip random number generator
    CPU_FEATURE_RDTSC       = 1 << 20,  // [x86/amd64 only] Time stamp counter
    CPU_FEATURE_CX8         = 1 << 21,  // [x86/amd64] CMPXCHG8B instruction
    CPU_FEATURE_CX16        = 1 << 22,  // [x86/amd64] CMPXCHG16B instruction,
    CPU_FEATURE_MONITOR     = 1 << 23,  // [x86/amd64] MONITOR/MWAIT instructions (SSE3)
    CPU_FEATURE_POPCNT      = 1 << 24,  // [x86/amd64] POPCNT instruction
    CPU_FEATURE_NEON        = 1 << 25,  // [arm64 only] ARM Vector extensions
    CPU_FEATURE_RVV         = 1 << 26   // [riscv only] RISC-V Vector extensions
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

const char* cpu_vendor_get_name(CPUVendor vendor);

/**
 * @return A bitmask of features available on the current processor.
 */
CPUFeature cpu_get_features();

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

cpu_bool cpu_is_initialized();

void cpu_set_exception_handler(CPUExceptionHandler handler);

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

cpu_usize cpu_popcnt16(cpu_u16 value);
cpu_usize cpu_popcnt32(cpu_u32 value);
cpu_usize cpu_popcnt64(cpu_u64 value);

LCPU_API_END