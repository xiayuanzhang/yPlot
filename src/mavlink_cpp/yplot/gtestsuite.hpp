/** @file
 *	@brief MAVLink comm testsuite protocol generated from yplot.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "yplot.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(yplot, PLOT)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::yplot::msg::PLOT packet_in{};
    packet_in.plotNum = -107;
    packet_in.plot = {{ 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0 }};

    mavlink::yplot::msg::PLOT packet1{};
    mavlink::yplot::msg::PLOT packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.plotNum, packet2.plotNum);
    EXPECT_EQ(packet1.plot, packet2.plot);
}

#ifdef TEST_INTEROP
TEST(yplot_interop, PLOT)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_plot_t packet_c {
         { 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0 }, -107
    };

    mavlink::yplot::msg::PLOT packet_in{};
    packet_in.plotNum = -107;
    packet_in.plot = {{ 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0 }};

    mavlink::yplot::msg::PLOT packet2{};

    mavlink_msg_plot_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.plotNum, packet2.plotNum);
    EXPECT_EQ(packet_in.plot, packet2.plot);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(yplot, PLOTNAME)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::yplot::msg::PLOTNAME packet_in{};
    packet_in.plotName0 = to_char_array("ABCDEFGHIJKLMN");
    packet_in.plotName1 = to_char_array("PQRSTUVWXYZABC");
    packet_in.plotName2 = to_char_array("EFGHIJKLMNOPQR");
    packet_in.plotName3 = to_char_array("TUVWXYZABCDEFG");
    packet_in.plotName4 = to_char_array("IJKLMNOPQRSTUV");
    packet_in.plotName5 = to_char_array("XYZABCDEFGHIJK");
    packet_in.plotName6 = to_char_array("MNOPQRSTUVWXYZ");
    packet_in.plotName7 = to_char_array("BCDEFGHIJKLMNO");
    packet_in.plotName8 = to_char_array("QRSTUVWXYZABCD");
    packet_in.plotName9 = to_char_array("FGHIJKLMNOPQRS");
    packet_in.plotName10 = to_char_array("UVWXYZABCDEFGH");
    packet_in.plotName11 = to_char_array("JKLMNOPQRSTUVW");

    mavlink::yplot::msg::PLOTNAME packet1{};
    mavlink::yplot::msg::PLOTNAME packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.plotName0, packet2.plotName0);
    EXPECT_EQ(packet1.plotName1, packet2.plotName1);
    EXPECT_EQ(packet1.plotName2, packet2.plotName2);
    EXPECT_EQ(packet1.plotName3, packet2.plotName3);
    EXPECT_EQ(packet1.plotName4, packet2.plotName4);
    EXPECT_EQ(packet1.plotName5, packet2.plotName5);
    EXPECT_EQ(packet1.plotName6, packet2.plotName6);
    EXPECT_EQ(packet1.plotName7, packet2.plotName7);
    EXPECT_EQ(packet1.plotName8, packet2.plotName8);
    EXPECT_EQ(packet1.plotName9, packet2.plotName9);
    EXPECT_EQ(packet1.plotName10, packet2.plotName10);
    EXPECT_EQ(packet1.plotName11, packet2.plotName11);
}

#ifdef TEST_INTEROP
TEST(yplot_interop, PLOTNAME)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_plotname_t packet_c {
         "ABCDEFGHIJKLMN", "PQRSTUVWXYZABC", "EFGHIJKLMNOPQR", "TUVWXYZABCDEFG", "IJKLMNOPQRSTUV", "XYZABCDEFGHIJK", "MNOPQRSTUVWXYZ", "BCDEFGHIJKLMNO", "QRSTUVWXYZABCD", "FGHIJKLMNOPQRS", "UVWXYZABCDEFGH", "JKLMNOPQRSTUVW"
    };

    mavlink::yplot::msg::PLOTNAME packet_in{};
    packet_in.plotName0 = to_char_array("ABCDEFGHIJKLMN");
    packet_in.plotName1 = to_char_array("PQRSTUVWXYZABC");
    packet_in.plotName2 = to_char_array("EFGHIJKLMNOPQR");
    packet_in.plotName3 = to_char_array("TUVWXYZABCDEFG");
    packet_in.plotName4 = to_char_array("IJKLMNOPQRSTUV");
    packet_in.plotName5 = to_char_array("XYZABCDEFGHIJK");
    packet_in.plotName6 = to_char_array("MNOPQRSTUVWXYZ");
    packet_in.plotName7 = to_char_array("BCDEFGHIJKLMNO");
    packet_in.plotName8 = to_char_array("QRSTUVWXYZABCD");
    packet_in.plotName9 = to_char_array("FGHIJKLMNOPQRS");
    packet_in.plotName10 = to_char_array("UVWXYZABCDEFGH");
    packet_in.plotName11 = to_char_array("JKLMNOPQRSTUVW");

    mavlink::yplot::msg::PLOTNAME packet2{};

    mavlink_msg_plotname_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.plotName0, packet2.plotName0);
    EXPECT_EQ(packet_in.plotName1, packet2.plotName1);
    EXPECT_EQ(packet_in.plotName2, packet2.plotName2);
    EXPECT_EQ(packet_in.plotName3, packet2.plotName3);
    EXPECT_EQ(packet_in.plotName4, packet2.plotName4);
    EXPECT_EQ(packet_in.plotName5, packet2.plotName5);
    EXPECT_EQ(packet_in.plotName6, packet2.plotName6);
    EXPECT_EQ(packet_in.plotName7, packet2.plotName7);
    EXPECT_EQ(packet_in.plotName8, packet2.plotName8);
    EXPECT_EQ(packet_in.plotName9, packet2.plotName9);
    EXPECT_EQ(packet_in.plotName10, packet2.plotName10);
    EXPECT_EQ(packet_in.plotName11, packet2.plotName11);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(yplot, USER)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::yplot::msg::USER packet_in{};
    packet_in.userData = {{ 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 0, 1, 2, 3 }};

    mavlink::yplot::msg::USER packet1{};
    mavlink::yplot::msg::USER packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.userData, packet2.userData);
}

#ifdef TEST_INTEROP
TEST(yplot_interop, USER)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_user_t packet_c {
         { 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 0, 1, 2, 3 }
    };

    mavlink::yplot::msg::USER packet_in{};
    packet_in.userData = {{ 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 0, 1, 2, 3 }};

    mavlink::yplot::msg::USER packet2{};

    mavlink_msg_user_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.userData, packet2.userData);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(yplot, PID)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::yplot::msg::PID packet_in{};
    packet_in.pidName = {{ 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 }};
    packet_in.p = 17.0;
    packet_in.i = 45.0;
    packet_in.d = 73.0;

    mavlink::yplot::msg::PID packet1{};
    mavlink::yplot::msg::PID packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.pidName, packet2.pidName);
    EXPECT_EQ(packet1.p, packet2.p);
    EXPECT_EQ(packet1.i, packet2.i);
    EXPECT_EQ(packet1.d, packet2.d);
}

#ifdef TEST_INTEROP
TEST(yplot_interop, PID)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_pid_t packet_c {
         17.0, 45.0, 73.0, { 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 }
    };

    mavlink::yplot::msg::PID packet_in{};
    packet_in.pidName = {{ 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 }};
    packet_in.p = 17.0;
    packet_in.i = 45.0;
    packet_in.d = 73.0;

    mavlink::yplot::msg::PID packet2{};

    mavlink_msg_pid_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.pidName, packet2.pidName);
    EXPECT_EQ(packet_in.p, packet2.p);
    EXPECT_EQ(packet_in.i, packet2.i);
    EXPECT_EQ(packet_in.d, packet2.d);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
