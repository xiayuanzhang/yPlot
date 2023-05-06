#pragma once
// MESSAGE USER PACKING

#define MAVLINK_MSG_ID_USER 3


typedef struct __mavlink_user_t {
 uint8_t userData[255]; /*<  cmd*/
} mavlink_user_t;

#define MAVLINK_MSG_ID_USER_LEN 255
#define MAVLINK_MSG_ID_USER_MIN_LEN 255
#define MAVLINK_MSG_ID_3_LEN 255
#define MAVLINK_MSG_ID_3_MIN_LEN 255

#define MAVLINK_MSG_ID_USER_CRC 202
#define MAVLINK_MSG_ID_3_CRC 202

#define MAVLINK_MSG_USER_FIELD_USERDATA_LEN 255

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_USER { \
    3, \
    "USER", \
    1, \
    {  { "userData", NULL, MAVLINK_TYPE_UINT8_T, 255, 0, offsetof(mavlink_user_t, userData) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_USER { \
    "USER", \
    1, \
    {  { "userData", NULL, MAVLINK_TYPE_UINT8_T, 255, 0, offsetof(mavlink_user_t, userData) }, \
         } \
}
#endif

/**
 * @brief Pack a user message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param userData  cmd
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_user_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *userData)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_USER_LEN];

    _mav_put_uint8_t_array(buf, 0, userData, 255);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_USER_LEN);
#else
    mavlink_user_t packet;

    mav_array_memcpy(packet.userData, userData, sizeof(uint8_t)*255);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_USER_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_USER;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_USER_MIN_LEN, MAVLINK_MSG_ID_USER_LEN, MAVLINK_MSG_ID_USER_CRC);
}

/**
 * @brief Pack a user message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param userData  cmd
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_user_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *userData)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_USER_LEN];

    _mav_put_uint8_t_array(buf, 0, userData, 255);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_USER_LEN);
#else
    mavlink_user_t packet;

    mav_array_memcpy(packet.userData, userData, sizeof(uint8_t)*255);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_USER_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_USER;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_USER_MIN_LEN, MAVLINK_MSG_ID_USER_LEN, MAVLINK_MSG_ID_USER_CRC);
}

/**
 * @brief Encode a user struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param user C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_user_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_user_t* user)
{
    return mavlink_msg_user_pack(system_id, component_id, msg, user->userData);
}

/**
 * @brief Encode a user struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param user C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_user_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_user_t* user)
{
    return mavlink_msg_user_pack_chan(system_id, component_id, chan, msg, user->userData);
}

/**
 * @brief Send a user message
 * @param chan MAVLink channel to send the message
 *
 * @param userData  cmd
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_user_send(mavlink_channel_t chan, const uint8_t *userData)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_USER_LEN];

    _mav_put_uint8_t_array(buf, 0, userData, 255);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_USER, buf, MAVLINK_MSG_ID_USER_MIN_LEN, MAVLINK_MSG_ID_USER_LEN, MAVLINK_MSG_ID_USER_CRC);
#else
    mavlink_user_t packet;

    mav_array_memcpy(packet.userData, userData, sizeof(uint8_t)*255);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_USER, (const char *)&packet, MAVLINK_MSG_ID_USER_MIN_LEN, MAVLINK_MSG_ID_USER_LEN, MAVLINK_MSG_ID_USER_CRC);
#endif
}

/**
 * @brief Send a user message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_user_send_struct(mavlink_channel_t chan, const mavlink_user_t* user)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_user_send(chan, user->userData);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_USER, (const char *)user, MAVLINK_MSG_ID_USER_MIN_LEN, MAVLINK_MSG_ID_USER_LEN, MAVLINK_MSG_ID_USER_CRC);
#endif
}

#if MAVLINK_MSG_ID_USER_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_user_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *userData)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_uint8_t_array(buf, 0, userData, 255);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_USER, buf, MAVLINK_MSG_ID_USER_MIN_LEN, MAVLINK_MSG_ID_USER_LEN, MAVLINK_MSG_ID_USER_CRC);
#else
    mavlink_user_t *packet = (mavlink_user_t *)msgbuf;

    mav_array_memcpy(packet->userData, userData, sizeof(uint8_t)*255);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_USER, (const char *)packet, MAVLINK_MSG_ID_USER_MIN_LEN, MAVLINK_MSG_ID_USER_LEN, MAVLINK_MSG_ID_USER_CRC);
#endif
}
#endif

#endif

// MESSAGE USER UNPACKING


/**
 * @brief Get field userData from user message
 *
 * @return  cmd
 */
static inline uint16_t mavlink_msg_user_get_userData(const mavlink_message_t* msg, uint8_t *userData)
{
    return _MAV_RETURN_uint8_t_array(msg, userData, 255,  0);
}

/**
 * @brief Decode a user message into a struct
 *
 * @param msg The message to decode
 * @param user C-struct to decode the message contents into
 */
static inline void mavlink_msg_user_decode(const mavlink_message_t* msg, mavlink_user_t* user)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_user_get_userData(msg, user->userData);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_USER_LEN? msg->len : MAVLINK_MSG_ID_USER_LEN;
        memset(user, 0, MAVLINK_MSG_ID_USER_LEN);
    memcpy(user, _MAV_PAYLOAD(msg), len);
#endif
}
