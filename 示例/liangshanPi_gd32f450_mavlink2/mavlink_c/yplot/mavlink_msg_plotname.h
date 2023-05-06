#pragma once
// MESSAGE PLOTNAME PACKING

#define MAVLINK_MSG_ID_PLOTNAME 2


typedef struct __mavlink_plotname_t {
 char plotName0[15]; /*<  serial plot name*/
 char plotName1[15]; /*<  serial plot name*/
 char plotName2[15]; /*<  serial plot name*/
 char plotName3[15]; /*<  serial plot name*/
 char plotName4[15]; /*<  serial plot name*/
 char plotName5[15]; /*<  serial plot name*/
 char plotName6[15]; /*<  serial plot name*/
 char plotName7[15]; /*<  serial plot name*/
 char plotName8[15]; /*<  serial plot name*/
 char plotName9[15]; /*<  serial plot name*/
 char plotName10[15]; /*<  serial plot name*/
 char plotName11[15]; /*<  serial plot name*/
} mavlink_plotname_t;

#define MAVLINK_MSG_ID_PLOTNAME_LEN 180
#define MAVLINK_MSG_ID_PLOTNAME_MIN_LEN 180
#define MAVLINK_MSG_ID_2_LEN 180
#define MAVLINK_MSG_ID_2_MIN_LEN 180

#define MAVLINK_MSG_ID_PLOTNAME_CRC 179
#define MAVLINK_MSG_ID_2_CRC 179

#define MAVLINK_MSG_PLOTNAME_FIELD_PLOTNAME0_LEN 15
#define MAVLINK_MSG_PLOTNAME_FIELD_PLOTNAME1_LEN 15
#define MAVLINK_MSG_PLOTNAME_FIELD_PLOTNAME2_LEN 15
#define MAVLINK_MSG_PLOTNAME_FIELD_PLOTNAME3_LEN 15
#define MAVLINK_MSG_PLOTNAME_FIELD_PLOTNAME4_LEN 15
#define MAVLINK_MSG_PLOTNAME_FIELD_PLOTNAME5_LEN 15
#define MAVLINK_MSG_PLOTNAME_FIELD_PLOTNAME6_LEN 15
#define MAVLINK_MSG_PLOTNAME_FIELD_PLOTNAME7_LEN 15
#define MAVLINK_MSG_PLOTNAME_FIELD_PLOTNAME8_LEN 15
#define MAVLINK_MSG_PLOTNAME_FIELD_PLOTNAME9_LEN 15
#define MAVLINK_MSG_PLOTNAME_FIELD_PLOTNAME10_LEN 15
#define MAVLINK_MSG_PLOTNAME_FIELD_PLOTNAME11_LEN 15

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PLOTNAME { \
    2, \
    "PLOTNAME", \
    12, \
    {  { "plotName0", NULL, MAVLINK_TYPE_CHAR, 15, 0, offsetof(mavlink_plotname_t, plotName0) }, \
         { "plotName1", NULL, MAVLINK_TYPE_CHAR, 15, 15, offsetof(mavlink_plotname_t, plotName1) }, \
         { "plotName2", NULL, MAVLINK_TYPE_CHAR, 15, 30, offsetof(mavlink_plotname_t, plotName2) }, \
         { "plotName3", NULL, MAVLINK_TYPE_CHAR, 15, 45, offsetof(mavlink_plotname_t, plotName3) }, \
         { "plotName4", NULL, MAVLINK_TYPE_CHAR, 15, 60, offsetof(mavlink_plotname_t, plotName4) }, \
         { "plotName5", NULL, MAVLINK_TYPE_CHAR, 15, 75, offsetof(mavlink_plotname_t, plotName5) }, \
         { "plotName6", NULL, MAVLINK_TYPE_CHAR, 15, 90, offsetof(mavlink_plotname_t, plotName6) }, \
         { "plotName7", NULL, MAVLINK_TYPE_CHAR, 15, 105, offsetof(mavlink_plotname_t, plotName7) }, \
         { "plotName8", NULL, MAVLINK_TYPE_CHAR, 15, 120, offsetof(mavlink_plotname_t, plotName8) }, \
         { "plotName9", NULL, MAVLINK_TYPE_CHAR, 15, 135, offsetof(mavlink_plotname_t, plotName9) }, \
         { "plotName10", NULL, MAVLINK_TYPE_CHAR, 15, 150, offsetof(mavlink_plotname_t, plotName10) }, \
         { "plotName11", NULL, MAVLINK_TYPE_CHAR, 15, 165, offsetof(mavlink_plotname_t, plotName11) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PLOTNAME { \
    "PLOTNAME", \
    12, \
    {  { "plotName0", NULL, MAVLINK_TYPE_CHAR, 15, 0, offsetof(mavlink_plotname_t, plotName0) }, \
         { "plotName1", NULL, MAVLINK_TYPE_CHAR, 15, 15, offsetof(mavlink_plotname_t, plotName1) }, \
         { "plotName2", NULL, MAVLINK_TYPE_CHAR, 15, 30, offsetof(mavlink_plotname_t, plotName2) }, \
         { "plotName3", NULL, MAVLINK_TYPE_CHAR, 15, 45, offsetof(mavlink_plotname_t, plotName3) }, \
         { "plotName4", NULL, MAVLINK_TYPE_CHAR, 15, 60, offsetof(mavlink_plotname_t, plotName4) }, \
         { "plotName5", NULL, MAVLINK_TYPE_CHAR, 15, 75, offsetof(mavlink_plotname_t, plotName5) }, \
         { "plotName6", NULL, MAVLINK_TYPE_CHAR, 15, 90, offsetof(mavlink_plotname_t, plotName6) }, \
         { "plotName7", NULL, MAVLINK_TYPE_CHAR, 15, 105, offsetof(mavlink_plotname_t, plotName7) }, \
         { "plotName8", NULL, MAVLINK_TYPE_CHAR, 15, 120, offsetof(mavlink_plotname_t, plotName8) }, \
         { "plotName9", NULL, MAVLINK_TYPE_CHAR, 15, 135, offsetof(mavlink_plotname_t, plotName9) }, \
         { "plotName10", NULL, MAVLINK_TYPE_CHAR, 15, 150, offsetof(mavlink_plotname_t, plotName10) }, \
         { "plotName11", NULL, MAVLINK_TYPE_CHAR, 15, 165, offsetof(mavlink_plotname_t, plotName11) }, \
         } \
}
#endif

/**
 * @brief Pack a plotname message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param plotName0  serial plot name
 * @param plotName1  serial plot name
 * @param plotName2  serial plot name
 * @param plotName3  serial plot name
 * @param plotName4  serial plot name
 * @param plotName5  serial plot name
 * @param plotName6  serial plot name
 * @param plotName7  serial plot name
 * @param plotName8  serial plot name
 * @param plotName9  serial plot name
 * @param plotName10  serial plot name
 * @param plotName11  serial plot name
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_plotname_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const char *plotName0, const char *plotName1, const char *plotName2, const char *plotName3, const char *plotName4, const char *plotName5, const char *plotName6, const char *plotName7, const char *plotName8, const char *plotName9, const char *plotName10, const char *plotName11)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLOTNAME_LEN];

    _mav_put_char_array(buf, 0, plotName0, 15);
    _mav_put_char_array(buf, 15, plotName1, 15);
    _mav_put_char_array(buf, 30, plotName2, 15);
    _mav_put_char_array(buf, 45, plotName3, 15);
    _mav_put_char_array(buf, 60, plotName4, 15);
    _mav_put_char_array(buf, 75, plotName5, 15);
    _mav_put_char_array(buf, 90, plotName6, 15);
    _mav_put_char_array(buf, 105, plotName7, 15);
    _mav_put_char_array(buf, 120, plotName8, 15);
    _mav_put_char_array(buf, 135, plotName9, 15);
    _mav_put_char_array(buf, 150, plotName10, 15);
    _mav_put_char_array(buf, 165, plotName11, 15);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLOTNAME_LEN);
#else
    mavlink_plotname_t packet;

    mav_array_memcpy(packet.plotName0, plotName0, sizeof(char)*15);
    mav_array_memcpy(packet.plotName1, plotName1, sizeof(char)*15);
    mav_array_memcpy(packet.plotName2, plotName2, sizeof(char)*15);
    mav_array_memcpy(packet.plotName3, plotName3, sizeof(char)*15);
    mav_array_memcpy(packet.plotName4, plotName4, sizeof(char)*15);
    mav_array_memcpy(packet.plotName5, plotName5, sizeof(char)*15);
    mav_array_memcpy(packet.plotName6, plotName6, sizeof(char)*15);
    mav_array_memcpy(packet.plotName7, plotName7, sizeof(char)*15);
    mav_array_memcpy(packet.plotName8, plotName8, sizeof(char)*15);
    mav_array_memcpy(packet.plotName9, plotName9, sizeof(char)*15);
    mav_array_memcpy(packet.plotName10, plotName10, sizeof(char)*15);
    mav_array_memcpy(packet.plotName11, plotName11, sizeof(char)*15);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLOTNAME_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLOTNAME;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PLOTNAME_MIN_LEN, MAVLINK_MSG_ID_PLOTNAME_LEN, MAVLINK_MSG_ID_PLOTNAME_CRC);
}

/**
 * @brief Pack a plotname message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param plotName0  serial plot name
 * @param plotName1  serial plot name
 * @param plotName2  serial plot name
 * @param plotName3  serial plot name
 * @param plotName4  serial plot name
 * @param plotName5  serial plot name
 * @param plotName6  serial plot name
 * @param plotName7  serial plot name
 * @param plotName8  serial plot name
 * @param plotName9  serial plot name
 * @param plotName10  serial plot name
 * @param plotName11  serial plot name
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_plotname_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const char *plotName0,const char *plotName1,const char *plotName2,const char *plotName3,const char *plotName4,const char *plotName5,const char *plotName6,const char *plotName7,const char *plotName8,const char *plotName9,const char *plotName10,const char *plotName11)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLOTNAME_LEN];

    _mav_put_char_array(buf, 0, plotName0, 15);
    _mav_put_char_array(buf, 15, plotName1, 15);
    _mav_put_char_array(buf, 30, plotName2, 15);
    _mav_put_char_array(buf, 45, plotName3, 15);
    _mav_put_char_array(buf, 60, plotName4, 15);
    _mav_put_char_array(buf, 75, plotName5, 15);
    _mav_put_char_array(buf, 90, plotName6, 15);
    _mav_put_char_array(buf, 105, plotName7, 15);
    _mav_put_char_array(buf, 120, plotName8, 15);
    _mav_put_char_array(buf, 135, plotName9, 15);
    _mav_put_char_array(buf, 150, plotName10, 15);
    _mav_put_char_array(buf, 165, plotName11, 15);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLOTNAME_LEN);
#else
    mavlink_plotname_t packet;

    mav_array_memcpy(packet.plotName0, plotName0, sizeof(char)*15);
    mav_array_memcpy(packet.plotName1, plotName1, sizeof(char)*15);
    mav_array_memcpy(packet.plotName2, plotName2, sizeof(char)*15);
    mav_array_memcpy(packet.plotName3, plotName3, sizeof(char)*15);
    mav_array_memcpy(packet.plotName4, plotName4, sizeof(char)*15);
    mav_array_memcpy(packet.plotName5, plotName5, sizeof(char)*15);
    mav_array_memcpy(packet.plotName6, plotName6, sizeof(char)*15);
    mav_array_memcpy(packet.plotName7, plotName7, sizeof(char)*15);
    mav_array_memcpy(packet.plotName8, plotName8, sizeof(char)*15);
    mav_array_memcpy(packet.plotName9, plotName9, sizeof(char)*15);
    mav_array_memcpy(packet.plotName10, plotName10, sizeof(char)*15);
    mav_array_memcpy(packet.plotName11, plotName11, sizeof(char)*15);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLOTNAME_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLOTNAME;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PLOTNAME_MIN_LEN, MAVLINK_MSG_ID_PLOTNAME_LEN, MAVLINK_MSG_ID_PLOTNAME_CRC);
}

/**
 * @brief Encode a plotname struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param plotname C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_plotname_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_plotname_t* plotname)
{
    return mavlink_msg_plotname_pack(system_id, component_id, msg, plotname->plotName0, plotname->plotName1, plotname->plotName2, plotname->plotName3, plotname->plotName4, plotname->plotName5, plotname->plotName6, plotname->plotName7, plotname->plotName8, plotname->plotName9, plotname->plotName10, plotname->plotName11);
}

/**
 * @brief Encode a plotname struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param plotname C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_plotname_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_plotname_t* plotname)
{
    return mavlink_msg_plotname_pack_chan(system_id, component_id, chan, msg, plotname->plotName0, plotname->plotName1, plotname->plotName2, plotname->plotName3, plotname->plotName4, plotname->plotName5, plotname->plotName6, plotname->plotName7, plotname->plotName8, plotname->plotName9, plotname->plotName10, plotname->plotName11);
}

/**
 * @brief Send a plotname message
 * @param chan MAVLink channel to send the message
 *
 * @param plotName0  serial plot name
 * @param plotName1  serial plot name
 * @param plotName2  serial plot name
 * @param plotName3  serial plot name
 * @param plotName4  serial plot name
 * @param plotName5  serial plot name
 * @param plotName6  serial plot name
 * @param plotName7  serial plot name
 * @param plotName8  serial plot name
 * @param plotName9  serial plot name
 * @param plotName10  serial plot name
 * @param plotName11  serial plot name
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_plotname_send(mavlink_channel_t chan, const char *plotName0, const char *plotName1, const char *plotName2, const char *plotName3, const char *plotName4, const char *plotName5, const char *plotName6, const char *plotName7, const char *plotName8, const char *plotName9, const char *plotName10, const char *plotName11)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLOTNAME_LEN];

    _mav_put_char_array(buf, 0, plotName0, 15);
    _mav_put_char_array(buf, 15, plotName1, 15);
    _mav_put_char_array(buf, 30, plotName2, 15);
    _mav_put_char_array(buf, 45, plotName3, 15);
    _mav_put_char_array(buf, 60, plotName4, 15);
    _mav_put_char_array(buf, 75, plotName5, 15);
    _mav_put_char_array(buf, 90, plotName6, 15);
    _mav_put_char_array(buf, 105, plotName7, 15);
    _mav_put_char_array(buf, 120, plotName8, 15);
    _mav_put_char_array(buf, 135, plotName9, 15);
    _mav_put_char_array(buf, 150, plotName10, 15);
    _mav_put_char_array(buf, 165, plotName11, 15);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLOTNAME, buf, MAVLINK_MSG_ID_PLOTNAME_MIN_LEN, MAVLINK_MSG_ID_PLOTNAME_LEN, MAVLINK_MSG_ID_PLOTNAME_CRC);
#else
    mavlink_plotname_t packet;

    mav_array_memcpy(packet.plotName0, plotName0, sizeof(char)*15);
    mav_array_memcpy(packet.plotName1, plotName1, sizeof(char)*15);
    mav_array_memcpy(packet.plotName2, plotName2, sizeof(char)*15);
    mav_array_memcpy(packet.plotName3, plotName3, sizeof(char)*15);
    mav_array_memcpy(packet.plotName4, plotName4, sizeof(char)*15);
    mav_array_memcpy(packet.plotName5, plotName5, sizeof(char)*15);
    mav_array_memcpy(packet.plotName6, plotName6, sizeof(char)*15);
    mav_array_memcpy(packet.plotName7, plotName7, sizeof(char)*15);
    mav_array_memcpy(packet.plotName8, plotName8, sizeof(char)*15);
    mav_array_memcpy(packet.plotName9, plotName9, sizeof(char)*15);
    mav_array_memcpy(packet.plotName10, plotName10, sizeof(char)*15);
    mav_array_memcpy(packet.plotName11, plotName11, sizeof(char)*15);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLOTNAME, (const char *)&packet, MAVLINK_MSG_ID_PLOTNAME_MIN_LEN, MAVLINK_MSG_ID_PLOTNAME_LEN, MAVLINK_MSG_ID_PLOTNAME_CRC);
#endif
}

/**
 * @brief Send a plotname message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_plotname_send_struct(mavlink_channel_t chan, const mavlink_plotname_t* plotname)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_plotname_send(chan, plotname->plotName0, plotname->plotName1, plotname->plotName2, plotname->plotName3, plotname->plotName4, plotname->plotName5, plotname->plotName6, plotname->plotName7, plotname->plotName8, plotname->plotName9, plotname->plotName10, plotname->plotName11);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLOTNAME, (const char *)plotname, MAVLINK_MSG_ID_PLOTNAME_MIN_LEN, MAVLINK_MSG_ID_PLOTNAME_LEN, MAVLINK_MSG_ID_PLOTNAME_CRC);
#endif
}

#if MAVLINK_MSG_ID_PLOTNAME_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_plotname_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const char *plotName0, const char *plotName1, const char *plotName2, const char *plotName3, const char *plotName4, const char *plotName5, const char *plotName6, const char *plotName7, const char *plotName8, const char *plotName9, const char *plotName10, const char *plotName11)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_char_array(buf, 0, plotName0, 15);
    _mav_put_char_array(buf, 15, plotName1, 15);
    _mav_put_char_array(buf, 30, plotName2, 15);
    _mav_put_char_array(buf, 45, plotName3, 15);
    _mav_put_char_array(buf, 60, plotName4, 15);
    _mav_put_char_array(buf, 75, plotName5, 15);
    _mav_put_char_array(buf, 90, plotName6, 15);
    _mav_put_char_array(buf, 105, plotName7, 15);
    _mav_put_char_array(buf, 120, plotName8, 15);
    _mav_put_char_array(buf, 135, plotName9, 15);
    _mav_put_char_array(buf, 150, plotName10, 15);
    _mav_put_char_array(buf, 165, plotName11, 15);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLOTNAME, buf, MAVLINK_MSG_ID_PLOTNAME_MIN_LEN, MAVLINK_MSG_ID_PLOTNAME_LEN, MAVLINK_MSG_ID_PLOTNAME_CRC);
#else
    mavlink_plotname_t *packet = (mavlink_plotname_t *)msgbuf;

    mav_array_memcpy(packet->plotName0, plotName0, sizeof(char)*15);
    mav_array_memcpy(packet->plotName1, plotName1, sizeof(char)*15);
    mav_array_memcpy(packet->plotName2, plotName2, sizeof(char)*15);
    mav_array_memcpy(packet->plotName3, plotName3, sizeof(char)*15);
    mav_array_memcpy(packet->plotName4, plotName4, sizeof(char)*15);
    mav_array_memcpy(packet->plotName5, plotName5, sizeof(char)*15);
    mav_array_memcpy(packet->plotName6, plotName6, sizeof(char)*15);
    mav_array_memcpy(packet->plotName7, plotName7, sizeof(char)*15);
    mav_array_memcpy(packet->plotName8, plotName8, sizeof(char)*15);
    mav_array_memcpy(packet->plotName9, plotName9, sizeof(char)*15);
    mav_array_memcpy(packet->plotName10, plotName10, sizeof(char)*15);
    mav_array_memcpy(packet->plotName11, plotName11, sizeof(char)*15);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLOTNAME, (const char *)packet, MAVLINK_MSG_ID_PLOTNAME_MIN_LEN, MAVLINK_MSG_ID_PLOTNAME_LEN, MAVLINK_MSG_ID_PLOTNAME_CRC);
#endif
}
#endif

#endif

// MESSAGE PLOTNAME UNPACKING


/**
 * @brief Get field plotName0 from plotname message
 *
 * @return  serial plot name
 */
static inline uint16_t mavlink_msg_plotname_get_plotName0(const mavlink_message_t* msg, char *plotName0)
{
    return _MAV_RETURN_char_array(msg, plotName0, 15,  0);
}

/**
 * @brief Get field plotName1 from plotname message
 *
 * @return  serial plot name
 */
static inline uint16_t mavlink_msg_plotname_get_plotName1(const mavlink_message_t* msg, char *plotName1)
{
    return _MAV_RETURN_char_array(msg, plotName1, 15,  15);
}

/**
 * @brief Get field plotName2 from plotname message
 *
 * @return  serial plot name
 */
static inline uint16_t mavlink_msg_plotname_get_plotName2(const mavlink_message_t* msg, char *plotName2)
{
    return _MAV_RETURN_char_array(msg, plotName2, 15,  30);
}

/**
 * @brief Get field plotName3 from plotname message
 *
 * @return  serial plot name
 */
static inline uint16_t mavlink_msg_plotname_get_plotName3(const mavlink_message_t* msg, char *plotName3)
{
    return _MAV_RETURN_char_array(msg, plotName3, 15,  45);
}

/**
 * @brief Get field plotName4 from plotname message
 *
 * @return  serial plot name
 */
static inline uint16_t mavlink_msg_plotname_get_plotName4(const mavlink_message_t* msg, char *plotName4)
{
    return _MAV_RETURN_char_array(msg, plotName4, 15,  60);
}

/**
 * @brief Get field plotName5 from plotname message
 *
 * @return  serial plot name
 */
static inline uint16_t mavlink_msg_plotname_get_plotName5(const mavlink_message_t* msg, char *plotName5)
{
    return _MAV_RETURN_char_array(msg, plotName5, 15,  75);
}

/**
 * @brief Get field plotName6 from plotname message
 *
 * @return  serial plot name
 */
static inline uint16_t mavlink_msg_plotname_get_plotName6(const mavlink_message_t* msg, char *plotName6)
{
    return _MAV_RETURN_char_array(msg, plotName6, 15,  90);
}

/**
 * @brief Get field plotName7 from plotname message
 *
 * @return  serial plot name
 */
static inline uint16_t mavlink_msg_plotname_get_plotName7(const mavlink_message_t* msg, char *plotName7)
{
    return _MAV_RETURN_char_array(msg, plotName7, 15,  105);
}

/**
 * @brief Get field plotName8 from plotname message
 *
 * @return  serial plot name
 */
static inline uint16_t mavlink_msg_plotname_get_plotName8(const mavlink_message_t* msg, char *plotName8)
{
    return _MAV_RETURN_char_array(msg, plotName8, 15,  120);
}

/**
 * @brief Get field plotName9 from plotname message
 *
 * @return  serial plot name
 */
static inline uint16_t mavlink_msg_plotname_get_plotName9(const mavlink_message_t* msg, char *plotName9)
{
    return _MAV_RETURN_char_array(msg, plotName9, 15,  135);
}

/**
 * @brief Get field plotName10 from plotname message
 *
 * @return  serial plot name
 */
static inline uint16_t mavlink_msg_plotname_get_plotName10(const mavlink_message_t* msg, char *plotName10)
{
    return _MAV_RETURN_char_array(msg, plotName10, 15,  150);
}

/**
 * @brief Get field plotName11 from plotname message
 *
 * @return  serial plot name
 */
static inline uint16_t mavlink_msg_plotname_get_plotName11(const mavlink_message_t* msg, char *plotName11)
{
    return _MAV_RETURN_char_array(msg, plotName11, 15,  165);
}

/**
 * @brief Decode a plotname message into a struct
 *
 * @param msg The message to decode
 * @param plotname C-struct to decode the message contents into
 */
static inline void mavlink_msg_plotname_decode(const mavlink_message_t* msg, mavlink_plotname_t* plotname)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_plotname_get_plotName0(msg, plotname->plotName0);
    mavlink_msg_plotname_get_plotName1(msg, plotname->plotName1);
    mavlink_msg_plotname_get_plotName2(msg, plotname->plotName2);
    mavlink_msg_plotname_get_plotName3(msg, plotname->plotName3);
    mavlink_msg_plotname_get_plotName4(msg, plotname->plotName4);
    mavlink_msg_plotname_get_plotName5(msg, plotname->plotName5);
    mavlink_msg_plotname_get_plotName6(msg, plotname->plotName6);
    mavlink_msg_plotname_get_plotName7(msg, plotname->plotName7);
    mavlink_msg_plotname_get_plotName8(msg, plotname->plotName8);
    mavlink_msg_plotname_get_plotName9(msg, plotname->plotName9);
    mavlink_msg_plotname_get_plotName10(msg, plotname->plotName10);
    mavlink_msg_plotname_get_plotName11(msg, plotname->plotName11);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PLOTNAME_LEN? msg->len : MAVLINK_MSG_ID_PLOTNAME_LEN;
        memset(plotname, 0, MAVLINK_MSG_ID_PLOTNAME_LEN);
    memcpy(plotname, _MAV_PAYLOAD(msg), len);
#endif
}
