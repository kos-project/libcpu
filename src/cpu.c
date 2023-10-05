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
 * @since 05/10/2023
 */

#include "cpu/cpu.h"

_Noreturn void cpu_halt() {
    while(true) {
        cpu_hint_spin();
    }
}

const char* cpu_feature_get_name(CPUFeature feature) {
    switch(feature) {// clang-format off
        case CPU_FEATURE_X87:     return "x87";
        case CPU_FEATURE_MMX:     return "MMX";
        case CPU_FEATURE_SSE:     return "SSE";
        case CPU_FEATURE_SSE2:    return "SSE2";
        case CPU_FEATURE_SSE3:    return "SSE3";
        case CPU_FEATURE_SSSE3:   return "SSSE3";
        case CPU_FEATURE_SSE4_1:  return "SSE4.1";
        case CPU_FEATURE_SSE4_2:  return "SSE4.2";
        case CPU_FEATURE_SSE4A:   return "SSE4a";
        case CPU_FEATURE_AVX:     return "AVX";
        case CPU_FEATURE_AVX2:    return "AVX2";
        case CPU_FEATURE_AVX512:  return "AVX512F";
        case CPU_FEATURE_FMA3:    return "FMA3";
        case CPU_FEATURE_FMA4:    return "FMA4";
        case CPU_FEATURE_XSAVE:   return "XSAVE";
        case CPU_FEATURE_FXSR:    return "FXSR";
        case CPU_FEATURE_NX:      return "NX";
        case CPU_FEATURE_RDRND:   return "RDRND";
        case CPU_FEATURE_RDSEED:  return "RDSEED";
        case CPU_FEATURE_RDTSC:   return "RDTSC";
        case CPU_FEATURE_CX8:     return "CX8";
        case CPU_FEATURE_CX16:    return "CX16";
        case CPU_FEATURE_MONITOR: return "MONITOR";
        case CPU_FEATURE_POPCNT:  return "POPCNT";
        case CPU_FEATURE_NEON:    return "NEON";
        case CPU_FEATURE_RVV:     return "RVV";
        default:                  return "Unknown";
    }// clang-format on
}

const char* cpu_vendor_get_name(CPUVendor vendor) {
    switch(vendor) {// clang-format off
        case CPU_VENDOR_AMD:        return "Advanced Micro Devices";
        case CPU_VENDOR_INTEL:      return "Intel";
        case CPU_VENDOR_CYRIX:      return "Cyrix";
        case CPU_VENDOR_TRANSMETA:  return "Transmeta";
        case CPU_VENDOR_VIA:        return "VIA Technologies";
        case CPU_VENDOR_SIS:        return "Silicon Integrated Systems";
        case CPU_VENDOR_UMC:        return "United Microelectronics";
        case CPU_VENDOR_RISE:       return "Rise";
        case CPU_VENDOR_NEXGEN:     return "NexGen";
        case CPU_VENDOR_NSC:        return "National Semiconductor";
        // Virtual CPU vendors
        case CPU_VENDOR_KVM:        return "KVM";
        case CPU_VENDOR_QEMU:       return "QEMU (TCG)";
        case CPU_VENDOR_HYPERV:     return "Microsoft HyperV";
        case CPU_VENDOR_PARALLELS:  return "Parallels";
        case CPU_VENDOR_VMWARE:     return "VMWare";
        case CPU_VENDOR_XENHVM:     return "XenHVM";
        case CPU_VENDOR_ACRN:       return "Project ACRN";
        case CPU_VENDOR_QNX:        return "QNX";
        case CPU_VENDOR_ROSETTA:    return "Rosetta";
        case CPU_VENDOR_BHYVE:      return "BHyve";
        case CPU_VENDOR_MSXTA:      return "Microsoft x86-to-ARM";
        default:                    return "Unknown";
    }// clang-format on
}