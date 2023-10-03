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
 * @since 25/09/2023
 */

#include <cpu/cpu.h>
#include <efitest/efitest.h>
#include <efitest/efitest_utils.h>

ETEST_DEFINE_TEST(test_get_vendor) {
    const CPUVendor vendor = cpu_get_vendor();
    ETEST_ASSERT_NE(vendor, CPU_VENDOR_UNKNOWN);
}

ETEST_DEFINE_TEST(test_vendor_get_name) {
    const CPUVendor vendor = cpu_get_vendor();
    ETEST_ASSERT_NE(vendor, CPU_VENDOR_UNKNOWN);
    const char* name = cpu_vendor_get_name(vendor);
    ETEST_ASSERT_GT(strlen(name), 0);
    efitest_log(L"Detected CPU vendor: %a", name);
}

ETEST_DEFINE_TEST(test_get_features) {
    const CPUFeature features = cpu_get_features();
    ETEST_ASSERT_NE(features, CPU_FEATURE_NONE);

    const cpu_usize num_features = cpu_popcnt32((cpu_u32) features);
    const CPUFeature* all_features = cpu_get_available_features();
    const cpu_usize num_all_features = cpu_get_num_available_features();
    cpu_usize last_feat_index = 0;

    for(cpu_usize index = 0; index < num_features; ++index) {
        for(cpu_usize feat_index = last_feat_index; feat_index < num_all_features; ++feat_index) {
            const CPUFeature feature = all_features[feat_index];
            if((features & feature) == feature) {
                efitest_log(L"Detected CPU feature: %a", cpu_feature_get_name(feature));
                last_feat_index = feat_index + 1;
                goto outer_end;
            }
        }
    outer_end:
    }
}

ETEST_DEFINE_TEST(test_init) {
    const CPUFeature features = cpu_get_features();
    ETEST_ASSERT_NE(features, CPU_FEATURE_NONE);
    cpu_init(features);
}

ETEST_DEFINE_TEST(test_hint_spin) {
    for(int index = 0; index < 100000000; ++index) {
        cpu_hint_spin();
    }
}

ETEST_DEFINE_TEST(test_popcnt16) {
    ETEST_ASSERT_EQ(cpu_popcnt16(0), 0);
    ETEST_ASSERT_EQ(cpu_popcnt16(1), 1);
    ETEST_ASSERT_EQ(cpu_popcnt16(0b1100110011001100), 8);
    ETEST_ASSERT_EQ(cpu_popcnt16(0b1111111111111111), 16);
}

ETEST_DEFINE_TEST(test_popcnt32) {
    ETEST_ASSERT_EQ(cpu_popcnt32(0), 0);
    ETEST_ASSERT_EQ(cpu_popcnt32(1), 1);
    ETEST_ASSERT_EQ(cpu_popcnt32(0b1100110011001100), 8);
    ETEST_ASSERT_EQ(cpu_popcnt32(0b1111111111111111), 16);
}

ETEST_DEFINE_TEST(test_popcnt64) {
    ETEST_ASSERT_EQ(cpu_popcnt64(0), 0);
    ETEST_ASSERT_EQ(cpu_popcnt64(1), 1);
    ETEST_ASSERT_EQ(cpu_popcnt64(0b1100110011001100), 8);
    ETEST_ASSERT_EQ(cpu_popcnt64(0b1111111111111111), 16);
}