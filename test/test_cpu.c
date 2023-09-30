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
}

ETEST_DEFINE_TEST(test_get_features) {
    const CPUFeature features = cpu_get_features();
    ETEST_ASSERT_NE(features, CPU_FEATURE_NONE);
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
}

ETEST_DEFINE_TEST(test_popcnt32) {
    ETEST_ASSERT_EQ(cpu_popcnt32(0), 0);
    ETEST_ASSERT_EQ(cpu_popcnt32(1), 1);
}

ETEST_DEFINE_TEST(test_popcnt64) {
    ETEST_ASSERT_EQ(cpu_popcnt64(0), 0);
    ETEST_ASSERT_EQ(cpu_popcnt64(1), 1);
}