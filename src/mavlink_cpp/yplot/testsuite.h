/** @file
 *    @brief MAVLink comm protocol testsuite generated from yplot.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef YPLOT_TESTSUITE_H
#define YPLOT_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_yplot(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

    mavlink_test_yplot(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_plot(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PLOT >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_plot_t packet_in = {
        { 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0 },149
    };
    mavlink_plot_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.plotNum = packet_in.plotNum;
        
        mav_array_memcpy(packet1.plot, packet_in.plot, sizeof(float)*12);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PLOT_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PLOT_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_plot_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_plot_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_plot_pack(system_id, component_id, &msg , packet1.plotNum , packet1.plot );
    mavlink_msg_plot_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_plot_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.plotNum , packet1.plot );
    mavlink_msg_plot_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_plot_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_plot_send(MAVLINK_COMM_1 , packet1.plotNum , packet1.plot );
    mavlink_msg_plot_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PLOT") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PLOT) != NULL);
#endif
}

static void mavlink_test_plotname(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PLOTNAME >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_plotname_t packet_in = {
        "ABCDEFGHIJKLMN","PQRSTUVWXYZABC","EFGHIJKLMNOPQR","TUVWXYZABCDEFG","IJKLMNOPQRSTUV","XYZABCDEFGHIJK","MNOPQRSTUVWXYZ","BCDEFGHIJKLMNO","QRSTUVWXYZABCD","FGHIJKLMNOPQRS","UVWXYZABCDEFGH","JKLMNOPQRSTUVW"
    };
    mavlink_plotname_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.plotName0, packet_in.plotName0, sizeof(char)*15);
        mav_array_memcpy(packet1.plotName1, packet_in.plotName1, sizeof(char)*15);
        mav_array_memcpy(packet1.plotName2, packet_in.plotName2, sizeof(char)*15);
        mav_array_memcpy(packet1.plotName3, packet_in.plotName3, sizeof(char)*15);
        mav_array_memcpy(packet1.plotName4, packet_in.plotName4, sizeof(char)*15);
        mav_array_memcpy(packet1.plotName5, packet_in.plotName5, sizeof(char)*15);
        mav_array_memcpy(packet1.plotName6, packet_in.plotName6, sizeof(char)*15);
        mav_array_memcpy(packet1.plotName7, packet_in.plotName7, sizeof(char)*15);
        mav_array_memcpy(packet1.plotName8, packet_in.plotName8, sizeof(char)*15);
        mav_array_memcpy(packet1.plotName9, packet_in.plotName9, sizeof(char)*15);
        mav_array_memcpy(packet1.plotName10, packet_in.plotName10, sizeof(char)*15);
        mav_array_memcpy(packet1.plotName11, packet_in.plotName11, sizeof(char)*15);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PLOTNAME_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PLOTNAME_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_plotname_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_plotname_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_plotname_pack(system_id, component_id, &msg , packet1.plotName0 , packet1.plotName1 , packet1.plotName2 , packet1.plotName3 , packet1.plotName4 , packet1.plotName5 , packet1.plotName6 , packet1.plotName7 , packet1.plotName8 , packet1.plotName9 , packet1.plotName10 , packet1.plotName11 );
    mavlink_msg_plotname_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_plotname_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.plotName0 , packet1.plotName1 , packet1.plotName2 , packet1.plotName3 , packet1.plotName4 , packet1.plotName5 , packet1.plotName6 , packet1.plotName7 , packet1.plotName8 , packet1.plotName9 , packet1.plotName10 , packet1.plotName11 );
    mavlink_msg_plotname_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_plotname_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_plotname_send(MAVLINK_COMM_1 , packet1.plotName0 , packet1.plotName1 , packet1.plotName2 , packet1.plotName3 , packet1.plotName4 , packet1.plotName5 , packet1.plotName6 , packet1.plotName7 , packet1.plotName8 , packet1.plotName9 , packet1.plotName10 , packet1.plotName11 );
    mavlink_msg_plotname_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PLOTNAME") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PLOTNAME) != NULL);
#endif
}

static void mavlink_test_user(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_USER >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_user_t packet_in = {
        { 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 0, 1, 2, 3 }
    };
    mavlink_user_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.userData, packet_in.userData, sizeof(uint8_t)*255);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_USER_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_USER_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_user_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_user_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_user_pack(system_id, component_id, &msg , packet1.userData );
    mavlink_msg_user_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_user_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.userData );
    mavlink_msg_user_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_user_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_user_send(MAVLINK_COMM_1 , packet1.userData );
    mavlink_msg_user_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("USER") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_USER) != NULL);
#endif
}

static void mavlink_test_pid(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PID >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_pid_t packet_in = {
        17.0,45.0,73.0,{ 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 }
    };
    mavlink_pid_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.p = packet_in.p;
        packet1.i = packet_in.i;
        packet1.d = packet_in.d;
        
        mav_array_memcpy(packet1.pidName, packet_in.pidName, sizeof(uint8_t)*20);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PID_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PID_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pid_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_pid_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pid_pack(system_id, component_id, &msg , packet1.pidName , packet1.p , packet1.i , packet1.d );
    mavlink_msg_pid_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pid_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.pidName , packet1.p , packet1.i , packet1.d );
    mavlink_msg_pid_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_pid_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_pid_send(MAVLINK_COMM_1 , packet1.pidName , packet1.p , packet1.i , packet1.d );
    mavlink_msg_pid_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("PID") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_PID) != NULL);
#endif
}

static void mavlink_test_yplot(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_plot(system_id, component_id, last_msg);
    mavlink_test_plotname(system_id, component_id, last_msg);
    mavlink_test_user(system_id, component_id, last_msg);
    mavlink_test_pid(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // YPLOT_TESTSUITE_H
