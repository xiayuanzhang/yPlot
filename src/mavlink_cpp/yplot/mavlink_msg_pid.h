#pragma once
// MESSAGE PID PACKING

#define MAVLINK_MSG_ID_PID 4


typedef struct __mavlink_pid_t {
 float p; /*<  p*/
 float i; /*<  i*/
 float d; /*<  d*/
 uint8_t pidName[20]; /*<  pidName*/
} mavlink_pid_t;

#define MAVLINK_MSG_ID_PID_LEN 32
#define MAVLINK_MSG_ID_PID_MIN_LEN 32
#define MAVLINK_MSG_ID_4_LEN 32
#define MAVLINK_MSG_ID_4_MIN_LEN 32

#define MAVLINK_MSG_ID_PID_CRC 130
#define MAVLINK_MSG_ID_4_CRC 130

#define MAVLINK_MSG_PID_FIELD_PIDNAME_LEN 20

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PID { \
    4, \
    "PID", \
    4, \
    {  { "pidName", NULL, MAVLINK_TYPE_UINT8_T, 20, 12, offsetof(mavlink_pid_t, pidName) }, \
         { "p", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_pid_t, p) }, \
         { "i", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_pid_t, i) }, \
         { "d", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_pid_t, d) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PID { \
    "PID", \
    4, \
    {  { "pidName", NULL, MAVLINK_TYPE_UINT8_T, 20, 12, offsetof(mavlink_pid_t, pidName) }, \
         { "p", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_pid_t, p) }, \
         { "i", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_pid_t, i) }, \
         { "d", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_pid_t, d) }, \
         } \
}
#endif

/**
 * @brief Pack a pid message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param pidName  pidName
 * @param p  p
 * @param i  i
 * @param d  d
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pid_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *pidName, float p, float i, float d)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PID_LEN];
    _mav_put_float(buf, 0, p);
    _mav_put_float(buf, 4, i);
    _mav_put_float(buf, 8, d);
    _mav_put_uint8_t_array(buf, 12, pidName, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PID_LEN);
#else
    mavlink_pid_t packet;
    packet.p = p;
    packet.i = i;
    packet.d = d;
    mav_array_memcpy(packet.pidName, pidName, sizeof(uint8_t)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PID_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PID;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PID_MIN_LEN, MAVLINK_MSG_ID_PID_LEN, MAVLINK_MSG_ID_PID_CRC);
}

/**
 * @brief Pack a pid message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pidName  pidName
 * @param p  p
 * @param i  i
 * @param d  d
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_pid_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *pidName,float p,float i,float d)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PID_LEN];
    _mav_put_float(buf, 0, p);
    _mav_put_float(buf, 4, i);
    _mav_put_float(buf, 8, d);
    _mav_put_uint8_t_array(buf, 12, pidName, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PID_LEN);
#else
    mavlink_pid_t packet;
    packet.p = p;
    packet.i = i;
    packet.d = d;
    mav_array_memcpy(packet.pidName, pidName, sizeof(uint8_t)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PID_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PID;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PID_MIN_LEN, MAVLINK_MSG_ID_PID_LEN, MAVLINK_MSG_ID_PID_CRC);
}

/**
 * @brief Encode a pid struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param pid C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pid_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_pid_t* pid)
{
    return mavlink_msg_pid_pack(system_id, component_id, msg, pid->pidName, pid->p, pid->i, pid->d);
}

/**
 * @brief Encode a pid struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param pid C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_pid_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_pid_t* pid)
{
    return mavlink_msg_pid_pack_chan(system_id, component_id, chan, msg, pid->pidName, pid->p, pid->i, pid->d);
}

/**
 * @brief Send a pid message
 * @param chan MAVLink channel to send the message
 *
 * @param pidName  pidName
 * @param p  p
 * @param i  i
 * @param d  d
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_pid_send(mavlink_channel_t chan, const uint8_t *pidName, float p, float i, float d)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PID_LEN];
    _mav_put_float(buf, 0, p);
    _mav_put_float(buf, 4, i);
    _mav_put_float(buf, 8, d);
    _mav_put_uint8_t_array(buf, 12, pidName, 20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PID, buf, MAVLINK_MSG_ID_PID_MIN_LEN, MAVLINK_MSG_ID_PID_LEN, MAVLINK_MSG_ID_PID_CRC);
#else
    mavlink_pid_t packet;
    packet.p = p;
    packet.i = i;
    packet.d = d;
    mav_array_memcpy(packet.pidName, pidName, sizeof(uint8_t)*20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PID, (const char *)&packet, MAVLINK_MSG_ID_PID_MIN_LEN, MAVLINK_MSG_ID_PID_LEN, MAVLINK_MSG_ID_PID_CRC);
#endif
}

/**
 * @brief Send a pid message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_pid_send_struct(mavlink_channel_t chan, const mavlink_pid_t* pid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_pid_send(chan, pid->pidName, pid->p, pid->i, pid->d);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PID, (const char *)pid, MAVLINK_MSG_ID_PID_MIN_LEN, MAVLINK_MSG_ID_PID_LEN, MAVLINK_MSG_ID_PID_CRC);
#endif
}

#if MAVLINK_MSG_ID_PID_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_pid_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *pidName, float p, float i, float d)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, p);
    _mav_put_float(buf, 4, i);
    _mav_put_float(buf, 8, d);
    _mav_put_uint8_t_array(buf, 12, pidName, 20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PID, buf, MAVLINK_MSG_ID_PID_MIN_LEN, MAVLINK_MSG_ID_PID_LEN, MAVLINK_MSG_ID_PID_CRC);
#else
    mavlink_pid_t *packet = (mavlink_pid_t *)msgbuf;
    packet->p = p;
    packet->i = i;
    packet->d = d;
    mav_array_memcpy(packet->pidName, pidName, sizeof(uint8_t)*20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PID, (const char *)packet, MAVLINK_MSG_ID_PID_MIN_LEN, MAVLINK_MSG_ID_PID_LEN, MAVLINK_MSG_ID_PID_CRC);
#endif
}
#endif

#endif

// MESSAGE PID UNPACKING


/**
 * @brief Get field pidName from pid message
 *
 * @return  pidName
 */
static inline uint16_t mavlink_msg_pid_get_pidName(const mavlink_message_t* msg, uint8_t *pidName)
{
    return _MAV_RETURN_uint8_t_array(msg, pidName, 20,  12);
}

/**
 * @brief Get field p from pid message
 *
 * @return  p
 */
static inline float mavlink_msg_pid_get_p(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field i from pid message
 *
 * @return  i
 */
static inline float mavlink_msg_pid_get_i(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field d from pid message
 *
 * @return  d
 */
static inline float mavlink_msg_pid_get_d(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a pid message into a struct
 *
 * @param msg The message to decode
 * @param pid C-struct to decode the message contents into
 */
static inline void mavlink_msg_pid_decode(const mavlink_message_t* msg, mavlink_pid_t* pid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    pid->p = mavlink_msg_pid_get_p(msg);
    pid->i = mavlink_msg_pid_get_i(msg);
    pid->d = mavlink_msg_pid_get_d(msg);
    mavlink_msg_pid_get_pidName(msg, pid->pidName);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PID_LEN? msg->len : MAVLINK_MSG_ID_PID_LEN;
        memset(pid, 0, MAVLINK_MSG_ID_PID_LEN);
    memcpy(pid, _MAV_PAYLOAD(msg), len);
#endif
}
