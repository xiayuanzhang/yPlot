/** @file
 *  @brief MAVLink comm protocol generated from yplot.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_YPLOT_H
#define MAVLINK_YPLOT_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_YPLOT.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_YPLOT_XML_HASH -6515800180164653692

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{1, 52, 49, 49, 0, 0, 0}, {2, 179, 180, 180, 0, 0, 0}, {3, 202, 255, 255, 0, 0, 0}, {4, 130, 32, 32, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_YPLOT

// ENUM DEFINITIONS


/** @brief used to indicate whether the line is valid */
#ifndef HAVE_ENUM_PLOT_ISVALID
#define HAVE_ENUM_PLOT_ISVALID
typedef enum PLOT_ISVALID
{
   PLOT_INVALID=0, /* the ch is invalid | */
   PLOT_VALID=1, /* the ch is valid | */
   PLOT_ISVALID_ENUM_END=2, /*  | */
} PLOT_ISVALID;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_plot.h"
#include "./mavlink_msg_plotname.h"
#include "./mavlink_msg_user.h"
#include "./mavlink_msg_pid.h"

// base include



#if MAVLINK_YPLOT_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_PLOT, MAVLINK_MESSAGE_INFO_PLOTNAME, MAVLINK_MESSAGE_INFO_USER, MAVLINK_MESSAGE_INFO_PID}
# define MAVLINK_MESSAGE_NAMES {{ "PID", 4 }, { "PLOT", 1 }, { "PLOTNAME", 2 }, { "USER", 3 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_YPLOT_H
