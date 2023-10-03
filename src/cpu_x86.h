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

typedef struct _CPUID_EBX_L7_0 {
    cpu_bool fsgsbase : 1;
    cpu_bool : 1;
    cpu_bool sgx : 1;
    cpu_bool bmi1 : 1;
    cpu_bool hle : 1;
    cpu_bool avx2 : 1;
    cpu_bool fdp_excptn_only : 1;
    cpu_bool smep : 1;
    cpu_bool bmi2 : 1;
    cpu_bool erms : 1;
    cpu_bool invpcid : 1;
    cpu_bool rtm : 1;
    cpu_bool rdtm_pqm : 1;
    cpu_bool : 1;
    cpu_bool mpx : 1;
    cpu_bool rdta_pqe : 1;
    cpu_bool avx512_f : 1;
    cpu_bool avx512_dq : 1;
    cpu_bool rdseed : 1;
    cpu_bool adx : 1;
    cpu_bool smap : 1;
    cpu_bool avx512_ifma : 1;
    cpu_bool : 1;
    cpu_bool clflushopt : 1;
    cpu_bool clwb : 1;
    cpu_bool pt : 1;
    cpu_bool avx512_pf : 1;
    cpu_bool avx512_er : 1;
    cpu_bool avx512_cd : 1;
    cpu_bool sha : 1;
    cpu_bool avx512_bw : 1;
    cpu_bool avx512_vl : 1;
} CPUID_EBX_L7_0;
LCPU_STATIC_ASSERT(sizeof(CPUID_EBX_L7_0) == 4, "Invalid structure size");

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
    cpu_bool : 1;
    cpu_bool sep : 1;
    cpu_bool mtrr : 1;
    cpu_bool pge : 1;
    cpu_bool mca : 1;
    cpu_bool cmov : 1;
    cpu_bool pat : 1;
    cpu_bool pse36 : 1;
    cpu_bool psn : 1;
    cpu_bool clfsh : 1;
    cpu_bool : 1;
    cpu_bool ds : 1;
    cpu_bool acpi : 1;
    cpu_bool mmx : 1;
    cpu_bool fxsr : 1;
    cpu_bool sse : 1;
    cpu_bool sse2 : 1;
    cpu_bool ss : 1;
    cpu_bool htt : 1;
    cpu_bool tm : 1;
    cpu_bool : 1;
    cpu_bool pbe : 1;
} CPUID_EDX_L1;
LCPU_STATIC_ASSERT(sizeof(CPUID_EDX_L1) == 4, "Invalid structure size");

typedef struct _CPUID_EDX_L6 {

} CPUID_EDX_L6;

typedef struct _CPUID_EDX_L7_0 {
    cpu_bool : 1;
    cpu_bool sgx_keys : 1;
    cpu_bool avx512_4vnniw : 1;
    cpu_bool avx512_4fmaps : 1;
    cpu_bool fsrm : 1;
    cpu_bool uintr : 1;
    cpu_u8 : 2;
    cpu_bool avx512_vp2intersect : 1;
    cpu_bool srdbs_ctrl : 1;
    cpu_bool mc_clear : 1;
    cpu_bool rtm_always_abort : 1;
    cpu_bool : 1;
    cpu_bool tsx_force_abort_msr : 1;
    cpu_bool serialize : 1;
    cpu_bool hybrid : 1;
    cpu_bool tsxldtrk : 1;
    cpu_bool : 1;
    cpu_bool pconfig : 1;
    cpu_bool lbr : 1;
    cpu_bool cet_ibt : 1;
    cpu_bool : 1;
    cpu_bool amx_tile : 1;
    cpu_bool amx_int8 : 1;
    cpu_bool spec_ctrl : 1;
    cpu_bool stibp : 1;
    cpu_bool l1d_flush : 1;
    cpu_bool ia32_arch_caps : 1;
    cpu_bool ia32_core_caps : 1;
    cpu_bool ssbd : 1;
} CPUID_EDX_L7_0;
LCPU_STATIC_ASSERT(sizeof(CPUID_EDX_L7_0) == 4, "Invalid structure size");

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
    cpu_bool : 1;
    cpu_bool ecc : 1;
    cpu_bool nx : 1;
    cpu_bool : 1;
    cpu_bool mmxext : 1;
    cpu_bool mmx : 1;
    cpu_bool fxsr : 1;
    cpu_bool fxsr_opt : 1;
    cpu_bool pdpe1gb : 1;
    cpu_bool rdtscp : 1;
    cpu_bool : 1;
    cpu_bool lm : 1;
    cpu_bool tdnowext : 1;
    cpu_bool tdnow : 1;
} CPUID_EDX_L80000001;
LCPU_STATIC_ASSERT(sizeof(CPUID_EDX_L80000001) == 4, "Invalid structure size");

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
    cpu_bool : 1;
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
LCPU_STATIC_ASSERT(sizeof(CPUID_ECX_L1) == 4, "Invalid structure size");

typedef struct _CPUID_ECX_L6 {

} CPUID_ECX_L6;

typedef struct _CPUID_ECX_L7_0 {
    cpu_bool prefetchwt1 : 1;
    cpu_bool avx512_vdmi : 1;
    cpu_bool umip : 1;
    cpu_bool pku : 1;
    cpu_bool ospke : 1;
    cpu_bool waitpkg : 1;
    cpu_bool avx512_vdmi2 : 1;
    cpu_bool cetss_shstk : 1;
    cpu_bool gfni : 1;
    cpu_bool vaes : 1;
    cpu_bool vpclmulqdq : 1;
    cpu_bool avx512_vnni : 1;
    cpu_bool avx512_bitalg : 1;
    cpu_bool tme : 1;
    cpu_bool avx512_vpopcntdq : 1;
    cpu_bool : 1;
    cpu_bool la57 : 1;
    cpu_u8 mawau : 5;
    cpu_bool rdpid : 1;
    cpu_bool kl : 1;
    cpu_bool bus_lock_detect : 1;
    cpu_bool cldemote : 1;
    cpu_bool : 1;
    cpu_bool movdiri : 1;
    cpu_bool movdir64b : 1;
    cpu_bool enqcmd : 1;
    cpu_bool sgx_lc : 1;
    cpu_bool pks : 1;
} CPUID_ECX_L7_0;
LCPU_STATIC_ASSERT(sizeof(CPUID_ECX_L7_0) == 4, "Invalid structure size");

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
    cpu_bool : 1;
    cpu_bool lwp : 1;
    cpu_bool fma4 : 1;
    cpu_bool tce : 1;
    cpu_bool : 1;
    cpu_bool nodeid_msr : 1;
    cpu_bool : 1;
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
LCPU_STATIC_ASSERT(sizeof(CPUID_ECX_L80000001) == 4, "Invalid structure size");

typedef struct _CPUID_EAX_L6 {
    cpu_bool dts : 1;
    cpu_bool itb : 1;
    cpu_bool arat : 1;
    cpu_bool : 1;
    cpu_bool pln : 1;
    cpu_bool ecmd : 1;
    cpu_bool ptm : 1;
    cpu_bool hwp : 1;
    cpu_bool hwp_notification : 1;
    cpu_bool hwp_activity_window : 1;
    cpu_bool hwp_energy_perf_pref : 1;
    cpu_bool hwp_package_level_req : 1;
    cpu_bool : 1;
    cpu_bool hdc : 1;
    cpu_bool itb_mt3 : 1;
    cpu_bool hwp_cap_interrupt : 1;
    cpu_bool hwp_peci_override : 1;
    cpu_bool hwp_flexible : 1;
    cpu_bool hwp_fast_req : 1;
    cpu_bool hw_feedback : 1;
    cpu_bool hwp_req_idle_ignore : 1;
    cpu_bool : 1;
    cpu_bool hwp_ctl : 1;
    cpu_bool itd : 1;
    cpu_bool thermal_interrupt : 1;
    cpu_u8 : 7;// Fill up to 32 bits
} CPUID_EAX_L6;
LCPU_STATIC_ASSERT(sizeof(CPUID_EAX_L6) == 4, "Invalid structure size");

typedef struct _CPUID {
    union {
        cpu_u32 value;
        CPUID_EBX_L6 leaf6;    // Leaf 6
        CPUID_EBX_L7_0 leaf7_0;// Leaf 7:0
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

LCPU_STATIC_ASSERT(sizeof(CPUID) <= (sizeof(void*) << 2), "CPUID structure is too large");

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
LCPU_STATIC_ASSERT(sizeof(CPU_CR0) == sizeof(void*), "Invalid structure size");

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
    cpu_bool : 1;
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
LCPU_STATIC_ASSERT(sizeof(CPU_CR4) == sizeof(void*), "Invalid structure size");

typedef struct _CPU_EFER {
    cpu_bool sce : 1;
    cpu_bool dpe : 1;
    cpu_bool sewbed : 1;
    cpu_bool gewbed : 1;
    cpu_bool l2d : 1;
    cpu_u8 : 2;
    cpu_bool lme : 1;
    cpu_bool : 1;
} CPU_EFER;

typedef struct _CPU_XCR0 {
    cpu_bool x87 : 1;
    cpu_bool sse : 1;
    cpu_bool avx : 1;
    cpu_bool bndreg : 1;
    cpu_bool bndcsr : 1;
    cpu_bool optmask : 1;
    cpu_bool zmm_hi256 : 1;
    cpu_bool hi16_zmm : 1;
    cpu_bool pt : 1;
    cpu_bool pkru : 1;
    cpu_bool pasid : 1;
    cpu_bool cet_u : 1;
    cpu_bool cet_s : 1;
    cpu_bool hdc : 1;
    cpu_bool uintr : 1;
    cpu_bool lbr : 1;
    cpu_bool hwp : 1;
    cpu_bool amx_tilecfg : 1;
    cpu_bool amx_tiledat : 1;
    cpu_bool apx : 1;
#ifdef CPU_64_BIT
    cpu_u64 : 44;
#else
    cpu_u32 : 24;
#endif
} CPU_XCR0;
LCPU_STATIC_ASSERT(sizeof(CPU_XCR0) == sizeof(void*), "Invalid structure size");

#endif// CPU_X86