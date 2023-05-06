#pragma once
// MESSAGE PLOT PACKING

#define MAVLINK_MSG_ID_PLOT 1


typedef struct __mavlink_plot_t {
 float plot[12]; /*<  serial plot*/
 int8_t plotNum; /*<  serial plot num */
} mavlink_plot_t;

#define MAVLINK_MSG_ID_PLOT_LEN 49
#define MAVLINK_MSG_ID_PLOT_MIN_LEN 49
#define MAVLINK_MSG_ID_1_LEN 49
#define MAVLINK_MSG_ID_1_MIN_LEN 49

#define MAVLINK_MSG_ID_PLOT_CRC 52
#define MAVLINK_MSG_ID_1_CRC 52

#define MAVLINK_MSG_PLOT_FIELD_PLOT_LEN 12

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PLOT { \
    1, \
    "PLOT", \
    2, \
    {  { "plotNum", NULL, MAVLINK_TYPE_INT8_T, 0, 48, offsetof(mavlink_plot_t, plotNum) }, \
         { "plot", NULL, MAVLINK_TYPE_FLOAT, 12, 0, offsetof(mavlink_plot_t, plot) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PLOT { \
    "PLOT", \
    2, \
    {  { "plotNum", NULL, MAVLINK_TYPE_INT8_T, 0, 48, offsetof(mavlink_plot_t, plotNum) }, \
         { "plot", NULL, MAVLINK_TYPE_FLOAT, 12, 0, offsetof(mavlink_plot_t, plot) }, \
         } \
}
#endif

/**
 * @brief Pack a plot message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param plotNum  serial plot num 
 * @param plot  serial plot
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_plot_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int8_t plotNum, const float *plot)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLOT_LEN];
    _mav_put_int8_t(buf, 48, plotNum);
    _mav_put_float_array(buf, 0, plot, 12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLOT_LEN);
#else
    mavlink_plot_t packet;
    packet.plotNum = plotNum;
    mav_array_memcpy(packet.plot, plot, sizeof(float)*12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLOT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLOT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PLOT_MIN_LEN, MAVLINK_MSG_ID_PLOT_LEN, MAVLINK_MSG_ID_PLOT_CRC);
}

/**
 * @brief Pack a plot message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param plotNum  serial plot num 
 * @param plot  serial plot
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_plot_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int8_t plotNum,const float *plot)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLOT_LEN];
    _mav_put_int8_t(buf, 48, plotNum);
    _mav_put_float_array(buf, 0, plot, 12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLOT_LEN);
#else
    mavlink_plot_t packet;
    packet.plotNum = plotNum;
    mav_array_memcpy(packet.plot, plot, sizeof(float)*12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLOT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLOT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PLOT_MIN_LEN, MAVLINK_MSG_ID_PLOT_LEN, MAVLINK_MSG_ID_PLOT_CRC);
}

/**
 * @brief Encode a plot struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param plot C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_plot_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_plot_t* plot)
{
    return mavlink_msg_plot_pack(system_id, component_id, msg, plot->plotNum, plot->plot);
}

/**
 * @brief Encode a plot struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param plot C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_plot_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_plot_t* plot)
{
    return mavlink_msg_plot_pack_chan(system_id, component_id, chan, msg, plot->plotNum, plot->plot);
}

/**
 * @brief Send a plot message
 * @param chan MAVLink channel to send the message
 *
 * @param plotNum  serial plot num 
 * @param plot  serial plot
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_plot_send(mavlink_channel_t chan, int8_t plotNum, const float *plot)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLOT_LEN];
    _mav_put_int8_t(buf, 48, plotNum);
    _mav_put_float_array(buf, 0, plot, 12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLOT, buf, MAVLINK_MSG_ID_PLOT_MIN_LEN, MAVLINK_MSG_ID_PLOT_LEN, MAVLINK_MSG_ID_PLOT_CRC);
#else
    mavlink_plot_t packet;
    packet.plotNum = plotNum;
    mav_array_memcpy(packet.plot, plot, sizeof(float)*12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLOT, (const char *)&packet, MAVLINK_MSG_ID_PLOT_MIN_LEN, MAVLINK_MSG_ID_PLOT_LEN, MAVLINK_MSG_ID_PLOT_CRC);
#endif
}

/**
 * @brief Send a plot message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_plot_send_struct(mavlink_channel_t chan, const mavlink_plot_t* plot)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_plot_send(chan, plot->plotNum, plot->plot);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLOT, (const char *)plot, MAVLINK_MSG_ID_PLOT_MIN_LEN, MAVLINK_MSG_ID_PLOT_LEN, MAVLINK_MSG_ID_PLOT_CRC);
#endif
}

#if MAVLINK_MSG_ID_PLOT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_plot_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int8_t plotNum, const float *plot)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int8_t(buf, 48, plotNum);
    _mav_put_float_array(buf, 0, plot, 12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLOT, buf, MAVLINK_MSG_ID_PLOT_MIN_LEN, MAVLINK_MSG_ID_PLOT_LEN, MAVLINK_MSG_ID_PLOT_CRC);
#else
    mavlink_plot_t *packet = (mavlink_plot_t *)msgbuf;
    packet->plotNum = plotNum;
    mav_array_memcpy(packet->plot, plot, sizeof(float)*12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLOT, (const char *)packet, MAVLINK_MSG_ID_PLOT_MIN_LEN, MAVLINK_MSG_ID_PLOT_LEN, MAVLINK_MSG_ID_PLOT_CRC);
#endif
}
#endif

#endif

// MESSAGE PLOT UNPACKING


/**
 * @brief Get field plotNum from plot message
 *
 * @return  serial plot num 
 */
static inline int8_t mavlink_msg_plot_get_plotNum(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  48);
}

/**
 * @brief Get field plot from plot message
 *
 * @return  serial plot
 */
static inline uint16_t mavlink_msg_plot_get_plot(const mavlink_message_t* msg, float *plot)
{
    return _MAV_RETURN_float_array(msg, plot, 12,  0);
}

/**
 * @brief Decode a plot message into a struct
 *
 * @param msg The message to decode
 * @param plot C-struct to decode the message contents into
 */
static inline void mavlink_msg_plot_decode(const mavlink_message_t* msg, mavlink_plot_t* plot)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_plot_get_plot(msg, plot->plot);
    plot->plotNum = mavlink_msg_plot_get_plotNum(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PLOT_LEN? msg->len : MAVLINK_MSG_ID_PLOT_LEN;
        memset(plot, 0, MAVLINK_MSG_ID_PLOT_LEN);
    memcpy(plot, _MAV_PAYLOAD(msg), len);
#endif
}
