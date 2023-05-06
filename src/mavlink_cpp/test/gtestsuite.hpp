/** @file
 *	@brief MAVLink comm testsuite protocol generated from test.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "test.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(test, TEST_TYPES)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::test::msg::TEST_TYPES packet_in{};
    packet_in.c = 'E';
    packet_in.s = to_char_array("FGHIJKLMN");
    packet_in.u8 = 198;
    packet_in.u16 = 24723;
    packet_in.u32 = 963502456;
    packet_in.u64 = 93372036854775807ULL;
    packet_in.s8 = 9;
    packet_in.s16 = 24827;
    packet_in.s32 = 963502664;
    packet_in.s64 = 93372036854776311LL;
    packet_in.f = 745.0;
    packet_in.d = 235.0;
    packet_in.u8_array = {{ 76, 77, 78 }};
    packet_in.u16_array = {{ 24931, 24932, 24933 }};
    packet_in.u32_array = {{ 963503080, 963503081, 963503082 }};
    packet_in.u64_array = {{ 93372036854777319, 93372036854777320, 93372036854777321 }};
    packet_in.s8_array = {{ 21, 22, 23 }};
    packet_in.s16_array = {{ 25243, 25244, 25245 }};
    packet_in.s32_array = {{ 963503704, 963503705, 963503706 }};
    packet_in.s64_array = {{ 93372036854778831, 93372036854778832, 93372036854778833 }};
    packet_in.f_array = {{ 941.0, 942.0, 943.0 }};
    packet_in.d_array = {{ 627.0, 628.0, 629.0 }};

    mavlink::test::msg::TEST_TYPES packet1{};
    mavlink::test::msg::TEST_TYPES packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.c, packet2.c);
    EXPECT_EQ(packet1.s, packet2.s);
    EXPECT_EQ(packet1.u8, packet2.u8);
    EXPECT_EQ(packet1.u16, packet2.u16);
    EXPECT_EQ(packet1.u32, packet2.u32);
    EXPECT_EQ(packet1.u64, packet2.u64);
    EXPECT_EQ(packet1.s8, packet2.s8);
    EXPECT_EQ(packet1.s16, packet2.s16);
    EXPECT_EQ(packet1.s32, packet2.s32);
    EXPECT_EQ(packet1.s64, packet2.s64);
    EXPECT_EQ(packet1.f, packet2.f);
    EXPECT_EQ(packet1.d, packet2.d);
    EXPECT_EQ(packet1.u8_array, packet2.u8_array);
    EXPECT_EQ(packet1.u16_array, packet2.u16_array);
    EXPECT_EQ(packet1.u32_array, packet2.u32_array);
    EXPECT_EQ(packet1.u64_array, packet2.u64_array);
    EXPECT_EQ(packet1.s8_array, packet2.s8_array);
    EXPECT_EQ(packet1.s16_array, packet2.s16_array);
    EXPECT_EQ(packet1.s32_array, packet2.s32_array);
    EXPECT_EQ(packet1.s64_array, packet2.s64_array);
    EXPECT_EQ(packet1.f_array, packet2.f_array);
    EXPECT_EQ(packet1.d_array, packet2.d_array);
}

#ifdef TEST_INTEROP
TEST(test_interop, TEST_TYPES)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_test_types_t packet_c {
         93372036854775807ULL, 93372036854776311LL, 235.0, { 93372036854777319, 93372036854777320, 93372036854777321 }, { 93372036854778831, 93372036854778832, 93372036854778833 }, { 627.0, 628.0, 629.0 }, 963502456, 963502664, 745.0, { 963503080, 963503081, 963503082 }, { 963503704, 963503705, 963503706 }, { 941.0, 942.0, 943.0 }, 24723, 24827, { 24931, 24932, 24933 }, { 25243, 25244, 25245 }, 'E', "FGHIJKLMN", 198, 9, { 76, 77, 78 }, { 21, 22, 23 }
    };

    mavlink::test::msg::TEST_TYPES packet_in{};
    packet_in.c = 'E';
    packet_in.s = to_char_array("FGHIJKLMN");
    packet_in.u8 = 198;
    packet_in.u16 = 24723;
    packet_in.u32 = 963502456;
    packet_in.u64 = 93372036854775807ULL;
    packet_in.s8 = 9;
    packet_in.s16 = 24827;
    packet_in.s32 = 963502664;
    packet_in.s64 = 93372036854776311LL;
    packet_in.f = 745.0;
    packet_in.d = 235.0;
    packet_in.u8_array = {{ 76, 77, 78 }};
    packet_in.u16_array = {{ 24931, 24932, 24933 }};
    packet_in.u32_array = {{ 963503080, 963503081, 963503082 }};
    packet_in.u64_array = {{ 93372036854777319, 93372036854777320, 93372036854777321 }};
    packet_in.s8_array = {{ 21, 22, 23 }};
    packet_in.s16_array = {{ 25243, 25244, 25245 }};
    packet_in.s32_array = {{ 963503704, 963503705, 963503706 }};
    packet_in.s64_array = {{ 93372036854778831, 93372036854778832, 93372036854778833 }};
    packet_in.f_array = {{ 941.0, 942.0, 943.0 }};
    packet_in.d_array = {{ 627.0, 628.0, 629.0 }};

    mavlink::test::msg::TEST_TYPES packet2{};

    mavlink_msg_test_types_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.c, packet2.c);
    EXPECT_EQ(packet_in.s, packet2.s);
    EXPECT_EQ(packet_in.u8, packet2.u8);
    EXPECT_EQ(packet_in.u16, packet2.u16);
    EXPECT_EQ(packet_in.u32, packet2.u32);
    EXPECT_EQ(packet_in.u64, packet2.u64);
    EXPECT_EQ(packet_in.s8, packet2.s8);
    EXPECT_EQ(packet_in.s16, packet2.s16);
    EXPECT_EQ(packet_in.s32, packet2.s32);
    EXPECT_EQ(packet_in.s64, packet2.s64);
    EXPECT_EQ(packet_in.f, packet2.f);
    EXPECT_EQ(packet_in.d, packet2.d);
    EXPECT_EQ(packet_in.u8_array, packet2.u8_array);
    EXPECT_EQ(packet_in.u16_array, packet2.u16_array);
    EXPECT_EQ(packet_in.u32_array, packet2.u32_array);
    EXPECT_EQ(packet_in.u64_array, packet2.u64_array);
    EXPECT_EQ(packet_in.s8_array, packet2.s8_array);
    EXPECT_EQ(packet_in.s16_array, packet2.s16_array);
    EXPECT_EQ(packet_in.s32_array, packet2.s32_array);
    EXPECT_EQ(packet_in.s64_array, packet2.s64_array);
    EXPECT_EQ(packet_in.f_array, packet2.f_array);
    EXPECT_EQ(packet_in.d_array, packet2.d_array);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
