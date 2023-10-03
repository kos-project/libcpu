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

#ifdef CPU_X86

#include "cpu/cpu_types.h"

typedef struct _CPUID_EBX_L6 {

} CPUID_EBX_L6;

typedef struct _CPUID_EDX_L1 {
    cpu_bool fpu : 1;
    cpu_bool vme : 1;
    cpu_bool de : 1;
    cpu_bool pse : 1;
    cpu_bool tsc : 1;
    cpu_bool msr : 1;
    cpu_bool pae : 1;
    cpu_bool mce : 1;
    cpu_bool cx8 : 1;
    cpu_bool apic : 1;
    cpu_bool _reserved0 : 1;
    cpu_bool sep : 1;
    cpu_bool mtrr : 1;
    cpu_bool pge : 1;
    cpu_bool mca : 1;
    cpu_bool cmov : 1;
    cpu_bool pat : 1;
    cpu_bool pse36 : 1;
    cpu_bool psn : 1;
    cpu_bool clfsh : 1;
    cpu_bool _reserved1 : 1;
    cpu_bool ds : 1;
    cpu_bool acpi : 1;
    cpu_bool mmx : 1;
    cpu_bool fxsr : 1;
    cpu_bool sse : 1;
    cpu_bool sse2 : 1;
    cpu_bool ss : 1;
    cpu_bool htt : 1;
    cpu_bool tm : 1;
    cpu_bool _reserved2 : 1;
    cpu_bool pbe : 1;
} CPUID_EDX_L1;

typedef struct _CPUID_EDX_L6 {

} CPUID_EDX_L6;

typedef struct _CPUID_EDX_L7_0 {

} CPUID_EDX_L7_0;

typedef struct _CPUID_EDX_L7_1 {

} CPUID_EDX_L7_1;

typedef struct _CPUID_EDX_L7_2 {

} CPUID_EDX_L7_2;

typedef struct _CPUID_EDX_L80000001 {
    cpu_bool fpu : 1;
    cpu_bool vme : 1;
    cpu_bool de : 1;
    cpu_bool pse : 1;
    cpu_bool tsc : 1;
    cpu_bool msr : 1;
    cpu_bool pae : 1;
    cpu_bool mce : 1;
    cpu_bool cx8 : 1;
    cpu_bool apic : 1;
    cpu_bool syscall_k6 : 1;
    cpu_bool syscall : 1;
    cpu_bool mtrr : 1;
    cpu_bool pge : 1;
    cpu_bool mca : 1;
    cpu_bool cmov : 1;
    cpu_bool pat : 1;
    cpu_bool pse36 : 1;
    cpu_bool _reserved0 : 1;
    cpu_bool ecc : 1;
    cpu_bool nx : 1;
    cpu_bool _reserved1 : 1;
    cpu_bool mmxext : 1;
    cpu_bool mmx : 1;
    cpu_bool fxsr : 1;
    cpu_bool fxsr_opt : 1;
    cpu_bool pdpe1gb : 1;
    cpu_bool rdtscp : 1;
    cpu_bool _reserved2 : 1;
    cpu_bool lm : 1;
    cpu_bool tdnowext : 1;
    cpu_bool tdnow : 1;
} CPUID_EDX_L80000001;

typedef struct _CPUID_ECX_L1 {
    cpu_bool sse3 : 1;
    cpu_bool pclmulqdq : 1;
    cpu_bool dtes64 : 1;
    cpu_bool monitor : 1;
    cpu_bool ds_cpl : 1;
    cpu_bool vmx : 1;
    cpu_bool smx : 1;
    cpu_bool est : 1;
    cpu_bool tm2 : 1;
    cpu_bool ssse3 : 1;
    cpu_bool cnxt_id : 1;
    cpu_bool sdbg : 1;
    cpu_bool fma : 1;
    cpu_bool cx16 : 1;
    cpu_bool xtpr : 1;
    cpu_bool pdcm : 1;
    cpu_bool _reserved0 : 1;
    cpu_bool pcid : 1;
    cpu_bool dca : 1;
    cpu_bool sse4_1 : 1;
    cpu_bool sse4_2 : 1;
    cpu_bool x2apic : 1;
    cpu_bool movbe : 1;
    cpu_bool popcnt : 1;
    cpu_bool tsc_deadline : 1;
    cpu_bool aes_ni : 1;
    cpu_bool xsave : 1;
    cpu_bool osxsave : 1;
    cpu_bool avx : 1;
    cpu_bool f16c : 1;
    cpu_bool rdrnd : 1;
    cpu_bool hypervisor : 1;
} CPUID_ECX_L1;

typedef struct _CPUID_ECX_L6 {

} CPUID_ECX_L6;

typedef struct _CPUID_ECX_L7_0 {

} CPUID_ECX_L7_0;

typedef struct _CPUID_ECX_L7_1 {

} CPUID_ECX_L7_1;

typedef struct _CPUID_ECX_L80000001 {
    cpu_bool lahf_lm : 1;
    cpu_bool cmp_legacy : 1;
    cpu_bool svm : 1;
    cpu_bool extapic : 1;
    cpu_bool cr8_legacy : 1;
    cpu_bool abm : 1;
    cpu_bool sse4a : 1;
    cpu_bool misalignsse : 1;
    cpu_bool tdnowprefetch : 1;
    cpu_bool osvw : 1;
    cpu_bool ibs : 1;
    cpu_bool xop : 1;
    cpu_bool skinit : 1;
    cpu_bool wdt : 1;
    cpu_bool _reserved0 : 1;
    cpu_bool lwp : 1;
    cpu_bool fma4 : 1;
    cpu_bool tce : 1;
    cpu_bool _reserved1 : 1;
    cpu_bool nodeid_msr : 1;
    cpu_bool _reserved2 : 1;
    cpu_bool tbm : 1;
    cpu_bool topoext : 1;
    cpu_bool perfctr_core : 1;
    cpu_bool perfctr_nb : 1;
    cpu_bool streamperfmon : 1;
    cpu_bool dbx : 1;
    cpu_bool perftsc : 1;
    cpu_bool pcx_l2i : 1;
    cpu_bool monitorx : 1;
    cpu_bool addr_mask_ext : 1;
} CPUID_ECX_L80000001;

typedef struct _CPUID_EAX_L6 {
    cpu_bool dts : 1;
    cpu_bool itb : 1;
    cpu_bool arat : 1;
    cpu_bool _reserved0 : 1;
    cpu_bool pln : 1;
    cpu_bool ecmd : 1;
    cpu_bool ptm : 1;
    cpu_bool hwp : 1;
    cpu_bool hwp_notification : 1;
    cpu_bool hwp_activity_window : 1;
    cpu_bool hwp_energy_perf_pref : 1;
    cpu_bool hwp_package_level_req : 1;
    cpu_bool _reserved1 : 1;
    cpu_bool hdc : 1;
    cpu_bool itb_mt3 : 1;
    cpu_bool hwp_cap_interrupt : 1;
    cpu_bool hwp_peci_override : 1;
    cpu_bool hwp_flexible : 1;
    cpu_bool hwp_fast_req : 1;
    cpu_bool hw_feedback : 1;
    cpu_bool hwp_req_idle_ignore : 1;
    cpu_bool _reserved2 : 1;
    cpu_bool hwp_ctl : 1;
    cpu_bool itd : 1;
    cpu_bool thermal_interrupt : 1;
    cpu_u8 _reserved3 : 8;// Fill up to 32 bits
} CPUID_EAX_L6;

typedef struct _CPUID {
    union {
        cpu_u32 value;
        CPUID_EBX_L6 leaf6;// Leaf 6
    } ebx;
    union {
        cpu_u32 value;
        CPUID_EDX_L1 leaf1;              // Leaf 1
        CPUID_EDX_L6 leaf6;              // Leaf 6
        CPUID_EDX_L7_0 leaf7_0;          // Leaf 7:0
        CPUID_EDX_L7_1 leaf7_1;          // Leaf 7:1
        CPUID_EDX_L7_2 leaf7_2;          // Leaf 7:2
        CPUID_EDX_L80000001 leaf80000001;// Leaf 80000001 (AMD only)
    } edx;
    union {
        cpu_u32 value;
        CPUID_ECX_L1 leaf1;              // Leaf 1
        CPUID_ECX_L6 leaf6;              // Leaf 6
        CPUID_ECX_L7_0 leaf7_0;          // Leaf 7:0
        CPUID_ECX_L7_1 leaf7_1;          // Leaf 7:1
        CPUID_ECX_L80000001 leaf80000001;// Leaf 80000001 (AMD only)
    } ecx;
    union {
        cpu_u32 value;
        CPUID_EAX_L6 leaf6;// Leaf 6
    } eax;
} CPUID;

typedef struct _CPU_CR0 {
    cpu_bool pe : 1;
    cpu_bool mp : 1;
    cpu_bool em : 1;
    cpu_bool ts : 1;
    cpu_bool et : 1;
    cpu_bool ne : 1;
    cpu_u16 : 10;
    cpu_bool wp : 1;
    cpu_bool : 1;
    cpu_bool am : 1;
    cpu_u16 : 10;
    cpu_bool nw : 1;
    cpu_bool cd : 1;
    cpu_bool pg : 1;
#if CPU_64_BIT
    cpu_u32 : 32;
#endif
} CPU_CR0;

typedef struct _CPU_CR4 {
    cpu_bool vme : 1;
    cpu_bool pvi : 1;
    cpu_bool tsd : 1;
    cpu_bool de : 1;
    cpu_bool pse : 1;
    cpu_bool pae : 1;
    cpu_bool mce : 1;
    cpu_bool pge : 1;
    cpu_bool pce : 1;
    cpu_bool osfxsr : 1;
    cpu_bool osxmmexcpt : 1;
    cpu_bool umip : 1;
    cpu_bool la57 : 1;
    cpu_bool vmxe : 1;
    cpu_bool smxe : 1;
    cpu_bool _reserved0 : 1;
    cpu_bool fsgsbase : 1;
    cpu_bool pcide : 1;
    cpu_bool osxsave : 1;
    cpu_bool kl : 1;
    cpu_bool smep : 1;
    cpu_bool smap : 1;
    cpu_bool pke : 1;
    cpu_bool cet : 1;
    cpu_bool pks : 1;
    cpu_bool uintr : 1;
    cpu_u8 : 6;
#ifdef CPU_64_BIT
    cpu_u32 : 32;
#endif
} CPU_CR4;

typedef struct _CPU_EFER {
    cpu_bool sce : 1;
    cpu_bool dpe : 1;
    cpu_bool sewbed : 1;
    cpu_bool gewbed : 1;
    cpu_bool l2d : 1;
} CPU_EFER;

#endif// CPU_X86