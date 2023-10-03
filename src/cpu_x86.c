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

#ifdef CPU_X86

#include "cpu_x86.h"
#include "assembler.h"
#include "cpu/cpu.h"
#include "memory.h"
#include "utils.h"

// clang-format off
#define DEFINE_CR_GET(r, t)                          \
    static void get_##r(t* value) {                  \
        _assemble(                                   \
            _ins(),                                  \
            _outs(_inout(value)),                    \
            _clobs(_sclob(ax)),                      \
            _emitI(mov _reg(r), _sreg(ax))           \
            _emitI(mov _sreg(ax), _get(_var(value))) \
        );                                           \
    }

#define DEFINE_CR_SET(r, t)                          \
    static void set_##r(const t* value) {            \
        _assemble(                                   \
            _ins(),                                  \
            _outs(_inout(value)),                    \
            _clobs(_sclob(ax)),                      \
            _emitI(mov _get(_var(value)), _sreg(ax)) \
            _emitI(mov _sreg(ax), _reg(r))           \
        );                                           \
    }
// clang-format on

// NOLINTBEGIN
static cpu_bool g_is_initialized;
static CPUExceptionHandler g_exception_handler;
static CPUFeature g_enabled_features = CPU_FEATURE_NONE;
// clang-format off
static CPUFeature g_available_features[] = {
#if defined(CPU_X86)
        CPU_FEATURE_X87,
        CPU_FEATURE_MMX,
        CPU_FEATURE_SSE,
        CPU_FEATURE_SSE2,
        CPU_FEATURE_SSE3,
        CPU_FEATURE_SSSE3,
        CPU_FEATURE_SSE4_1,
        CPU_FEATURE_SSE4_2,
        CPU_FEATURE_SSE4A,
        CPU_FEATURE_AVX,
        CPU_FEATURE_AVX2,
        CPU_FEATURE_AVX512,
        CPU_FEATURE_FMA3,
        CPU_FEATURE_FMA4,
        CPU_FEATURE_FXSR,
        CPU_FEATURE_XSAVE,
        CPU_FEATURE_CX8,
        CPU_FEATURE_CX16,
        CPU_FEATURE_MONITOR,
#elif defined(CPU_ARM)
        CPU_FEATURE_NEON,
#elif defined(CPU_RISCV)
        CPU_FEATURE_RVV,
#endif
        // Abstracted general-purpose features
        CPU_FEATURE_POPCNT,
        CPU_FEATURE_NX,
        CPU_FEATURE_RDRND,
        CPU_FEATURE_RDTSC,
};
// clang-format on
// NOLINTEND

DEFINE_CR_GET(cr0, CPU_CR0)
DEFINE_CR_SET(cr0, CPU_CR0)
DEFINE_CR_GET(cr4, CPU_CR4)
DEFINE_CR_SET(cr4, CPU_CR4)

static void get_xcr0(CPU_XCR0* value) {
    _assemble(// clang-format off
        _ins(),
        _outs(_inout(value)),
        _clobs(_clob(rcx), _clob(edx), _clob(eax)),
        _emitI(xor _reg(rcx), _reg(rcx))
        _emitI(xgetbv)
        _emitI(mov _reg(edx), _get(_var(value), 0x04))
        _emitI(mov _reg(eax), _get(_var(value), 0x00))
    );// clang-format on
}

static void set_xcr0(const CPU_XCR0* value) {
    _assemble(// clang-format off
        _ins(),
        _outs(_inout(value)),
        _clobs(_clob(rcx), _clob(edx), _clob(eax)),
        _emitI(xor _reg(rcx), _reg(rcx))
        _emitI(mov _get(_var(value), 0x04), _reg(edx))
        _emitI(mov _get(_var(value), 0x00), _reg(eax))
        _emitI(xsetbv)
    );// clang-format on
}

static void init_xsave() {
    CPU_CR4 cr4;
    get_cr4(&cr4);
    if(cr4.osxsave && cr4.osxmmexcpt) {
        return;
    }
    cr4.osxsave = LCPU_TRUE;
    cr4.osxmmexcpt = LCPU_TRUE;
    set_cr4(&cr4);
}

static void init_fxsr() {
    CPU_CR4 cr4;
    get_cr4(&cr4);
    if(cr4.osfxsr) {
        return;
    }
    cr4.osfxsr = LCPU_TRUE;
    set_cr4(&cr4);
}

static void init_fpu() {
    _assemble(_ins(), _outs(), _clobs(), _emitI(fninit));
    CPU_CR0 cr0;
    get_cr0(&cr0);
    cr0.em = LCPU_FALSE;// Disable x87 emulation
    cr0.mp = LCPU_TRUE; // Enable co-processor monitoring
    set_cr0(&cr0);

    if((cpu_get_features() & CPU_FEATURE_XSAVE) == CPU_FEATURE_XSAVE) {
        CPU_XCR0 xcr0;
        get_xcr0(&xcr0);
        if(xcr0.x87) {
            return;
        }
        xcr0.x87 = LCPU_TRUE;
        set_xcr0(&xcr0);
    }
}

static void init_sse() {
    CPU_XCR0 xcr0;
    get_xcr0(&xcr0);
    if(xcr0.sse) {
        return;
    }
    xcr0.sse = LCPU_TRUE;
    set_xcr0(&xcr0);
}

static void init_avx() {
    CPU_XCR0 xcr0;
    get_xcr0(&xcr0);
    if(xcr0.avx) {
        return;
    }
    xcr0.avx = LCPU_TRUE;
    set_xcr0(&xcr0);
}

static void cpuid(cpu_u32 leaf, cpu_u32 sub_leaf, CPUID* value) {
    _assemble(// clang-format off
        _ins(_in(leaf), _in(sub_leaf)),
        _outs(_inout(value)),
        _clobs(_clob(eax), _clob(ebx), _clob(edx), _clob(ecx)),
        _emitI(mov _var(leaf), _reg(eax))
        _emitI(mov _var(sub_leaf), _reg(ecx))
        _emitI(cpuid)
        _emitI(mov _reg(ebx), _get(_var(value), 0x00))
        _emitI(mov _reg(edx), _get(_var(value), 0x04))
        _emitI(mov _reg(ecx), _get(_var(value), 0x08))
        _emitI(mov _reg(eax), _get(_var(value), 0x0C))
    );// clang-format on
}

cpu_usize cpu_get_gpr_width() {
    return LCPU_GPR_BITS;
}

cpu_usize cpu_get_vr_width() {
    const CPUFeature features = cpu_get_features();
    if((features & CPU_FEATURE_AVX512) != 0) {
        return 512;
    }
    if((features & CPU_FEATURE_AVX) != 0) {
        return 256;
    }
    if((features & CPU_FEATURE_SSE) != 0) {
        return 128;
    }
    if((features & CPU_FEATURE_MMX) != 0) {
        return 64;
    }
    return cpu_get_gpr_width();
}

CPUVendor cpu_get_vendor() {
    CPUID info;
    cpuid(0, 0, &info);// CPUID leaf 0 for 12-char vendor code

    RETURN_IF_MATCH(&info, "AMDisbetter!", 12, CPU_VENDOR_AMD);// Very early AMD chips used this
    RETURN_IF_MATCH(&info, "AuthenticAMD", 12, CPU_VENDOR_AMD);
    RETURN_IF_MATCH(&info, "GenuineIntel", 12, CPU_VENDOR_INTEL);
    RETURN_IF_MATCH(&info, "CyrixInstead", 12, CPU_VENDOR_CYRIX);
    RETURN_IF_MATCH(&info, "CentaurHauls", 12, CPU_VENDOR_VIA);
    RETURN_IF_MATCH(&info, "VIA VIA VIA ", 12, CPU_VENDOR_VIA);
    RETURN_IF_MATCH(&info, "GenuineTMx86", 12, CPU_VENDOR_TRANSMETA);
    RETURN_IF_MATCH(&info, "SiS SiS SiS ", 12, CPU_VENDOR_SIS);
    RETURN_IF_MATCH(&info, "UMC UMC UMC ", 12, CPU_VENDOR_UMC);
    RETURN_IF_MATCH(&info, "RiseRiseRise", 12, CPU_VENDOR_RISE);
    RETURN_IF_MATCH(&info, "NexGenDriven", 12, CPU_VENDOR_NEXGEN);
    RETURN_IF_MATCH(&info, "Geode by NSC", 12, CPU_VENDOR_NSC);
    // Virtual CPUs
    RETURN_IF_MATCH(&info, "KVMKVMKVMKVM", 12, CPU_VENDOR_KVM);
    RETURN_IF_MATCH(&info, "KVMKVMKVM\0\0\0", 12, CPU_VENDOR_KVM);
    RETURN_IF_MATCH(&info, "TCGTCGTCGTCG", 12, CPU_VENDOR_QEMU);
    RETURN_IF_MATCH(&info, "Microsoft Hv", 12, CPU_VENDOR_HYPERV);
    RETURN_IF_MATCH(&info, " lrpepyh  vr", 12, CPU_VENDOR_PARALLELS);
    RETURN_IF_MATCH(&info, "VMwareVMware", 12, CPU_VENDOR_VMWARE);
    RETURN_IF_MATCH(&info, "XenVMMXenVMM", 12, CPU_VENDOR_XENHVM);
    RETURN_IF_MATCH(&info, "ACRNACRNACRN", 12, CPU_VENDOR_ACRN);
    RETURN_IF_MATCH(&info, " QNXQVMBSQG ", 12, CPU_VENDOR_QNX);
    RETURN_IF_MATCH(&info, "VirtualApple", 12, CPU_VENDOR_ROSETTA);
    RETURN_IF_MATCH(&info, "bhyve bhyve ", 12, CPU_VENDOR_BHYVE);
    RETURN_IF_MATCH(&info, "MicrosoftXTA", 12, CPU_VENDOR_MSXTA);

    return CPU_VENDOR_UNKNOWN;
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

CPUFeature cpu_get_features() {
    CPUFeature features = CPU_FEATURE_NONE;
    CPUID info;
    cpuid(1, 0, &info);
    // EDX
    SET_BIT_IF(info.edx.leaf1.fpu, features, CPU_FEATURE_X87);
    SET_BIT_IF(info.edx.leaf1.mmx, features, CPU_FEATURE_MMX);
    SET_BIT_IF(info.edx.leaf1.sse, features, CPU_FEATURE_SSE);
    SET_BIT_IF(info.edx.leaf1.sse2, features, CPU_FEATURE_SSE2);
    SET_BIT_IF(info.edx.leaf1.cx8, features, CPU_FEATURE_CX8);
    SET_BIT_IF(info.edx.leaf1.fxsr, features, CPU_FEATURE_FXSR);
    SET_BIT_IF(info.edx.leaf1.tsc, features, CPU_FEATURE_RDTSC);
    // ECX
    SET_BIT_IF(info.ecx.leaf1.sse3, features, CPU_FEATURE_SSE3);
    SET_BIT_IF(info.ecx.leaf1.ssse3, features, CPU_FEATURE_SSSE3);
    SET_BIT_IF(info.ecx.leaf1.sse4_1, features, CPU_FEATURE_SSE4_1);
    SET_BIT_IF(info.ecx.leaf1.sse4_2, features, CPU_FEATURE_SSE4_2);
    SET_BIT_IF(info.ecx.leaf1.avx, features, CPU_FEATURE_AVX);
    SET_BIT_IF(info.ecx.leaf1.fma, features, CPU_FEATURE_FMA3);
    SET_BIT_IF(info.ecx.leaf1.xsave, features, CPU_FEATURE_XSAVE);
    SET_BIT_IF(info.ecx.leaf1.popcnt, features, CPU_FEATURE_POPCNT);
    SET_BIT_IF(info.ecx.leaf1.cx16, features, CPU_FEATURE_CX16);
    SET_BIT_IF(info.ecx.leaf1.rdrnd, features, CPU_FEATURE_RDRND);

    cpuid(7, 0, &info);
    // EBX
    SET_BIT_IF(info.ebx.leaf7_0.avx2, features, CPU_FEATURE_AVX2);
    SET_BIT_IF(info.ebx.leaf7_0.avx512_f, features, CPU_FEATURE_AVX512);

    cpuid(0x80000001, 0, &info);
    // ECX
    SET_BIT_IF(info.ecx.leaf80000001.sse4a, features, CPU_FEATURE_SSE4A);
    SET_BIT_IF(info.ecx.leaf80000001.fma4, features, CPU_FEATURE_FMA4);
    SET_BIT_IF(info.edx.leaf80000001.nx, features, CPU_FEATURE_NX);

    return features;
}

CPUFeature cpu_get_enabled_features() {
    return g_enabled_features;
}

const CPUFeature* cpu_get_available_features() {
    return g_available_features;
}

cpu_usize cpu_get_num_available_features() {
    return LCPU_ARRAYLEN(g_available_features);
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

void cpu_reset_state() {
    g_is_initialized = LCPU_FALSE;
    g_enabled_features = CPU_FEATURE_NONE;
}

void cpu_init(CPUFeature features) {
    if(g_is_initialized) {
        return;// Ignore all calls
    }
    CALL_IF_ENABLED(features, CPU_FEATURE_FXSR, init_fxsr);
    CALL_IF_ENABLED(features, CPU_FEATURE_XSAVE, init_xsave);
    CALL_IF_ENABLED(features, CPU_FEATURE_X87, init_fpu);
    CALL_IF_ENABLED(features, CPU_FEATURE_X87 | CPU_FEATURE_MMX, init_fpu);
    CALL_IF_ENABLED(features, CPU_FEATURE_XSAVE | CPU_FEATURE_FXSR | CPU_FEATURE_MMX | CPU_FEATURE_SSE, init_sse);
    CALL_IF_ENABLED(features, CPU_FEATURE_SSE | CPU_FEATURE_SSE2, init_sse);
#ifdef CPU_64_BIT
    CALL_IF_ENABLED(features, CPU_FEATURE_SSE2 | CPU_FEATURE_SSE3, init_sse);
    CALL_IF_ENABLED(features, CPU_FEATURE_SSE3 | CPU_FEATURE_SSSE3, init_sse);
    CALL_IF_ENABLED(features, CPU_FEATURE_SSSE3 | CPU_FEATURE_SSE4_1, init_sse);
    CALL_IF_ENABLED(features, CPU_FEATURE_SSE4_1 | CPU_FEATURE_SSE4_2, init_sse);
    CALL_IF_ENABLED(features, CPU_FEATURE_SSE4_2 | CPU_FEATURE_SSE4A, init_sse);
    CALL_IF_ENABLED(features, CPU_FEATURE_SSE4_2 | CPU_FEATURE_AVX, init_avx);
    CALL_IF_ENABLED(features, CPU_FEATURE_AVX | CPU_FEATURE_AVX2, init_avx);
    CALL_IF_ENABLED(features, CPU_FEATURE_AVX2 | CPU_FEATURE_AVX512, init_avx);
#endif
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
    _assemble(_ins(), _outs(), _clobs(), _emitI(pause));
}

_Noreturn void cpu_halt() {
    while(true) {
        cpu_hint_spin();
    }
}

static cpu_usize kernigham_popcnt32(cpu_u32 value) {
    cpu_usize count = 0;
    while(value != 0) {
        value &= (value - 1);
        ++count;
    }
    return count;
}

cpu_usize cpu_popcnt16(cpu_u16 value) {
    if((cpu_get_features() & CPU_FEATURE_POPCNT) != 0) {
        cpu_u16 result = 0;
        _assemble(// clang-format off
            _ins(_in(value)),
            _outs(_out(result)),
            _clobs(_clob(ax), _clob(bx)),
            _emitI(mov _var(value), _reg(ax))
            _emitI(popcnt _reg(ax), _reg(bx))
            _emitI(mov _reg(bx), _var(result))
        );// clang-format on
        return (cpu_usize) result;
    }
    return kernigham_popcnt32((cpu_u32) value);
}

cpu_usize cpu_popcnt32(cpu_u32 value) {
    if((cpu_get_features() & CPU_FEATURE_POPCNT) != 0) {
        cpu_u32 result = 0;
        _assemble(// clang-format off
            _ins(_in(value)),
            _outs(_out(result)),
            _clobs(_clob(eax), _clob(ebx)),
            _emitI(mov _var(value), _reg(eax))
            _emitI(popcnt _reg(eax), _reg(ebx))
            _emitI(mov _reg(ebx), _var(result))
        );// clang-format on
        return (cpu_usize) result;
    }
    return kernigham_popcnt32((cpu_u32) value);
}

cpu_usize cpu_popcnt64(cpu_u64 value) {
#ifdef CPU_64_BIT
    if((cpu_get_features() & CPU_FEATURE_POPCNT) != 0) {
        cpu_u64 result = 0;
        _assemble(// clang-format off
            _ins(_in(value)),
            _outs(_out(result)),
            _clobs(_clob(rax), _clob(rbx)),
            _emitI(mov _var(value), _reg(rax))
            _emitI(popcnt _reg(rax), _reg(rbx))
            _emitI(mov _reg(rbx), _var(result))
        );// clang-format on
        return (cpu_usize) result;
    }
#endif
    cpu_usize count = 0;
    while(value != 0) {
        value &= (value - 1);
        ++count;
    }
    return count;
}

#endif// CPU_X86